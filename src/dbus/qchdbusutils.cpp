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
#include <QMetaMethod>
#include <QDBusArgument>

QVariantList QchDBusUtils::convertMethodCallArguments(const QDBusInterface &iface, const QVariantList &arguments) {
    Q_UNUSED(iface);
    //TODO: Check DBus method argument types and convert if necessary.
    QVariantList args;

    foreach (QVariant arg, arguments) {
        switch (arg.type()) {
        case QVariant::Double:
            args.append(arg.toInt());
            break;
        case QVariant::List:
            args.append(arg.toStringList());
            break;
        default:
            args.append(arg);
            break;
        }
    }

    return args;
}

QVariant QchDBusUtils::dbusArgumentToVariant(const QDBusArgument &arg) {
    switch (arg.currentType()) {
    case QDBusArgument::BasicType:
    case QDBusArgument::VariantType:
        return QchDBusUtils::basicTypeToVariant(arg);
    case QDBusArgument::ArrayType:
        return QchDBusUtils::arrayTypeToVariant(arg);
    case QDBusArgument::MapType:
        return QchDBusUtils::mapTypeToVariant(arg);
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
        list.append(QchDBusUtils::dbusArgumentToVariant(arg));
    }

    arg.endArray();
    return list;
}

QVariant QchDBusUtils::mapTypeToVariant(const QDBusArgument &arg) {
    QVariantMap map;
    arg.beginMap();

    while (!arg.atEnd()) {
        arg.beginMapEntry();
        map[QchDBusUtils::basicTypeToVariant(arg).toString()] = QchDBusUtils::dbusArgumentToVariant(arg);
        arg.endMapEntry();
    }

    arg.endMap();
    return map;
}
