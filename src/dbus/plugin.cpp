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

#include "plugin_p.h"
#include "dbusadaptor_p.h"
#include "dbusmessage_p.h"

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.dbus"));

    qmlRegisterType<DBusAdaptor>(uri, 1, 0, "DBusAdaptor");
    qmlRegisterType<DBusMessage>(uri, 1, 0, "DBusMessage");
}

#include "moc_plugin_p.cpp"

Q_EXPORT_PLUGIN2(hildondbus, Plugin)
