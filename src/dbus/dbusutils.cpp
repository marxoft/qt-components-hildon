/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "dbusutils_p.h"
#include <QDBusInterface>
#include <QMetaMethod>
#include <QDBusArgument>

QVariantList DBusUtils::convertMethodCallArguments(const QDBusInterface &iface, const QVariantList &arguments) {
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

QVariant DBusUtils::dbusArgumentToVariant(const QDBusArgument &arg) {
    switch (arg.currentType()) {
    case QDBusArgument::BasicType:
    case QDBusArgument::VariantType:
        return DBusUtils::basicTypeToVariant(arg);
    case QDBusArgument::ArrayType:
        return DBusUtils::arrayTypeToVariant(arg);
    case QDBusArgument::MapType:
        return DBusUtils::mapTypeToVariant(arg);
    default:
        return QVariant();
    }
}

QVariant DBusUtils::basicTypeToVariant(const QDBusArgument &arg) {
    return arg.asVariant();
}

QVariant DBusUtils::arrayTypeToVariant(const QDBusArgument &arg) {
    QVariantList list;
    arg.beginArray();

    while (!arg.atEnd()) {
        list.append(DBusUtils::dbusArgumentToVariant(arg));
    }

    arg.endArray();
    return list;
}

QVariant DBusUtils::mapTypeToVariant(const QDBusArgument &arg) {
    QVariantMap map;
    arg.beginMap();

    while (!arg.atEnd()) {
        arg.beginMapEntry();
        map[DBusUtils::basicTypeToVariant(arg).toString()] = DBusUtils::dbusArgumentToVariant(arg);
        arg.endMapEntry();
    }

    arg.endMap();
    return map;
}
