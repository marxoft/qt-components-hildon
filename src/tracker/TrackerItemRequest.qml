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

import org.hildon.components 1.0
import org.hildon.dbus 1.0

QtObject {
    id: root

    default property variant children

    property string itemType: "Files"
    property string uri

    property variant properties: []
    property variant metaData // read-only

    property bool autoUpdate

    property int status // read-only

    function reload() {
        root.metaData = {};
        getter.send();
    }

    function setMetaData(map) {
        var args = [ root.itemType, root.uri ];
        var properties = [];
        var values = [];

        for (var attribute in map) {
            properties.push(attribute);
            values.push(map[attribute]);
        }

        args.push(properties);
        args.push(values);
        setter.arguments = args;
        setter.send();
    }

    DBusMessage {
        id: getter

        serviceName: "org.freedesktop.Tracker"
        path: "/org/freedesktop/Tracker/Metadata"
        interfaceName: "org.freedesktop.Tracker.Metadata"
        methodName: "Get"
        arguments: [ root.itemType, root.uri, root.properties ]
        onStatusChanged: {
            if (status == DBusMessage.Ready) {
                var data = {};
                
                for (var i = 0; i < reply.length; i++) {
                    data[properties[i]] = reply[i];
                }

                root.metaData = data;
            }

            root.status = status;
        }
    }

    DBusMessage {
        id: setter

        serviceName: "org.freedesktop.Tracker"
        path: "/org/freedesktop/Tracker/Metadata"
        interfaceName: "org.freedesktop.Tracker.Metadata"
        methodName: "Set"
        onStatusChanged: root.status = status
    }
}
