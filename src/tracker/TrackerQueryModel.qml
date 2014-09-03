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

ListModel {
    id: root

    property alias filter: request.filter
    property alias itemType: request.itemType
    property alias properties: request.properties
    property alias keywords: request.keywords
    property alias sortProperties: request.sortProperties
    property alias sortDescending: request.sortDescending
    property alias offset: request.offset
    property alias limit: request.limit
    property alias autoUpdate: request.autoUpdate

    property int status // read-only

    function reload() {
        request.reload();
    }

    TrackerQueryRequest {
        id: request

        onStatusChanged: {
            switch (status) {
            case 1:
                root.clear();
                break;
            case 2: {
                for (var i = 0; i < results.length; i++) {
                    root.append(results[i]);
                }
                
                request.clear();
                break;
            }
            default:
                break;
            }

            root.status = status;
        }
    }
}
