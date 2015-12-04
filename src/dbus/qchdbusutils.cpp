/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchdbusutils.h"
#include <QDBusInterface>
#include <QDBusArgument>
#include <QDBusMetaType>
#include <QMetaMethod>
#include <QMetaObject>

template<typename T> static QList<T> toQList(const QVariantList &list) {
    QList<T> arr;
    
    foreach(const QVariant &v, list) {
        arr << qvariant_cast<T>(v);
    }
    
    return arr;
}

static QStringList toQStringList(const QVariantList &list) {
    QStringList arr;
    
    foreach(const QVariant &v, list) {
        arr << qvariant_cast<QString>(v);
    }
    
    return arr;
}

static QByteArray toQByteArray(const QVariantList &list) {
    QByteArray arr;
    
    foreach(const QVariant &v, list) {
        uchar tmp = static_cast<uchar>(v.toUInt());
        arr.append(static_cast<char>(tmp));
    }
    
    return arr;
}

static void registerDBusTypes(void) {
    static bool done = false;

    if( !done ) {
        done = true;

        qDBusRegisterMetaType< QList<bool> >();
        qDBusRegisterMetaType< QList<int> >();
        qDBusRegisterMetaType< QList<double> >();
    }
}

static void convertListArgument(QVariant &arg) {
    QVariantList list = arg.toList();
    
    if (list.isEmpty()) {
        return;
    }
    
    const int type = list.at(0).type();
    
    for (int i = 1; i < list.size(); i++) {
        if (list.at(i).type() != type) {
            arg = list;
            return;
        }
    }
    
    switch (type) {
    case QVariant::String:
        arg = QVariant::fromValue(toQStringList(list));
        break;
    case QVariant::Bool:
        arg = QVariant::fromValue(toQList<bool>(list));
        break;
    case QVariant::Int:
        arg = QVariant::fromValue(toQList<int>(list));
        break;
    case QVariant::Double:
        arg = QVariant::fromValue(toQList<double>(list));
        break;
    }
}

static void convertMapArgument(QVariant &arg) {
    QVariantMap map = arg.toMap();
    
    foreach (const QString &key, map.keys()) {
        const int type = map.value(key).type();
        
        switch (type) {
        case QVariant::List:
        case QVariant::StringList:
            convertListArgument(map[key]);
            break;
        case QVariant::Map:
            convertMapArgument(map[key]);
        default:
            break;
        }
    }
    
    arg = map;
}

QVariantList QchDBusUtils::convertMethodCallArguments(const QDBusInterface &iface, const QString &methodName,
                                                      const QVariantList &arguments) {
    if (arguments.isEmpty()) {
        return arguments;
    }
    
    registerDBusTypes();
    
    QList<int> knownIds;
    bool matchFound = false;
    QVariantList args = arguments;
    QVariantList params;
    const QMetaObject *mo = iface.metaObject();
    QByteArray match = methodName.toLatin1();
    match += '(';
    
    for (int i = mo->methodOffset(); i < mo->methodCount(); i++) {
        const QMetaMethod mm = mo->method(i);
        const QByteArray signature = mm.signature();
        
        if (signature.startsWith(match)) {
            knownIds << i;
        }
    }
    
    if (knownIds.isEmpty()) {
        return args;
    }
    
    while ((!matchFound) && (!knownIds.isEmpty())) {
        args = arguments;
        params.clear();
        const QMetaMethod mm = mo->method(knownIds.takeFirst());
        QList<QByteArray> types = mm.parameterTypes();
        
        for (int i = 0; i < types.size(); i++) {
            if (types.at(i).endsWith('&')) {
                while (types.size() > 1) {
                    types.removeLast();
                }
                
                break;
            }
        }
        
        for (int i = 0; (!args.isEmpty()) && (i < types.size()); i++) {
            int id = QVariant::nameToType(types.at(i));
            
            if (id == QVariant::UserType) {
                id = QMetaType::type(types.at(i));
            }
            
            Q_ASSERT(id);
            QVariant p = args.takeFirst();
            
            if (id == int(QMetaType::UChar)) {
                p = qVariantFromValue<uchar>(p.toUInt());
            }
            else if (id < int(QMetaType::User)) {
                if ((id == int(QVariant::List)) || (id == int(QVariant::StringList))) {
                    convertListArgument(p);
                }
                else if (id == int(QVariant::Map)) {
                    convertMapArgument(p);
                }
                else {
                    p.convert(QVariant::Type(id));
                }
            }
            else if (id == qMetaTypeId<QDBusVariant>()) {
                QDBusVariant tmp(p);
                p = qVariantFromValue(tmp);
            }
            else if (id == qMetaTypeId<QDBusObjectPath>()) {
                QDBusObjectPath path(p.toString());
                p = qVariantFromValue(path);
            }
            else if (id == qMetaTypeId<QDBusSignature>()) {
                QDBusSignature sig(p.toString());
                p = qVariantFromValue(sig);
            }
            
            params << p;
        }
        
        matchFound = (params.size() == types.size()) && (args.isEmpty());
    }
    
    return params;       
}

QList<QchDBusMethod> QchDBusUtils::getSignals(const QDBusInterface &iface) {
    QList<QchDBusMethod> dbusSignals;
    const QMetaObject *mo = iface.metaObject();
    
    for (int i = mo->methodOffset(); i < mo->methodCount(); i++) {
        const QMetaMethod mm = mo->method(i);
        
        if (mm.methodType() == QMetaMethod::Signal) {
            QList<QByteArray> paramNames;
            const QByteArray methodSignature = QMetaObject::normalizedSignature(mm.signature());
            const QByteArray methodName = methodSignature.left(methodSignature.indexOf('('));
            const int paramCount = mm.parameterTypes().size();
            
            for (int i = 0; i < paramCount; i++) {
                paramNames << "arg" + QByteArray::number(i + 1);
            }
            
            dbusSignals << QchDBusMethod(methodName, paramNames);
        }
    }
    
    return dbusSignals;
}

QList<QByteArray> QchDBusUtils::getSignalNames(const QDBusInterface &iface) {
    QList<QByteArray> names;
    const QMetaObject *mo = iface.metaObject();
    
    for (int i = mo->methodOffset(); i < mo->methodCount(); i++) {
        const QMetaMethod mm = mo->method(i);
        
        if (mm.methodType() == QMetaMethod::Signal) {
            const QByteArray methodSignature = QMetaObject::normalizedSignature(mm.signature());
            const QByteArray methodName = methodSignature.left(methodSignature.indexOf('('));
            names << methodName;
        }
    }
    
    return names;
}

QVariant QchDBusUtils::dbusArgumentToVariant(const QDBusArgument &argument) {
    switch (argument.currentType()) {
    case QDBusArgument::BasicType:
    case QDBusArgument::VariantType:
        return basicTypeToVariant(argument);
    case QDBusArgument::ArrayType:
        return arrayTypeToVariant(argument);
    case QDBusArgument::MapType:
        return mapTypeToVariant(argument);
    case QDBusArgument::StructureType:
        return structureTypeToVariant(argument);
    default:
        return QVariant();
    }
}

QVariant QchDBusUtils::basicTypeToVariant(const QDBusArgument &arg) {
    return arg.asVariant();
}

QVariant QchDBusUtils::arrayTypeToVariant(const QDBusArgument &arg) {
    QVariantList list;
    arg.beginArray();

    while (!arg.atEnd()) {
        list.append(dbusArgumentToVariant(arg));
    }

    arg.endArray();
    return list;
}

QVariant QchDBusUtils::mapTypeToVariant(const QDBusArgument &arg) {
    QVariantMap map;
    arg.beginMap();

    while (!arg.atEnd()) {
        arg.beginMapEntry();
        map[basicTypeToVariant(arg).toString()] = dbusArgumentToVariant(arg);
        arg.endMapEntry();
    }

    arg.endMap();
    return map;
}

QVariant QchDBusUtils::structureTypeToVariant(const QDBusArgument &arg) {
    QVariantList list;
    arg.beginStructure();

    while (!arg.atEnd()) {
        list.append(QchDBusUtils::dbusArgumentToVariant(arg));
    }

    arg.endStructure();
    return list;
}
