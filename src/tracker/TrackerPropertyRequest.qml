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

    property QtObject filter

    property string itemType: "Files"
    
    property variant properties: []

    property int offset
    property int limit: 10000
    property int status // read-only

    property bool sortDescending
    property bool autoUpdate

    property variant results: [] // read-only

    function reload() {
        root.clear();
        message.send();
    }

    function clear() {
        root.results = [];
    }

    DBusMessage {
        id: message

        serviceName: "org.freedesktop.Tracker"
        path: "/org/freedesktop/Tracker/Metadata"
        interfaceName: "org.freedesktop.Tracker.Metadata"
        methodName: "GetUniqueValues"
        arguments: [
            root.itemType,
            root.properties,
            root.filter ? "<rdfq:Condition> " + root.filter.condition() + " </rdfq:Condition>" : "",
            root.sortDescending,
            root.offset,
            root.limit
        ]
        onStatusChanged: {
            if (status == DBusMessage.Ready) {
                var items = [];

                for (var i = 0; i < reply.length; i++) {
                    var result = reply[i];
                    var item = {};

                    try {
                        for (var j = 0; j < result.length; j++) {
                            item[root.properties[j]] = result[j];
                        }
                    }
                    catch (e) {
                        console.log(e);
                    }

                    items.push(item);
                }

                root.results = items;
            }

            root.status = status;
        }
    }
}
