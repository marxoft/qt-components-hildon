/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchplugin.h"
#include "qchdbusconnections.h"
#include "qchdbusmessage.h"

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.dbus"));
    
    qmlRegisterType<QchDBusConnections>(uri, 1, 0, "DBusConnections");
    qmlRegisterType<QchDBusMessage>(uri, 1, 0, "DBusMessage");
        
    qmlRegisterUncreatableType<QchDBus>(uri, 1, 0, "DBus", "");
}

Q_EXPORT_PLUGIN2(qchdbus, QchPlugin)
