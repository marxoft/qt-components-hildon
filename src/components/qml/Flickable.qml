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

import QtQuick 1.0

Flickable {
    id: root
        
    property int horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
    property int verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
    
    interactive: (contentWidth > width) || (contentHeight > height)
    
    Component {
        id: horizontalScrollBar
        
        ScrollBar {    
            flickableItem: root
            orientation: Qt.Horizontal
            scrollBarPolicy: root.horizontalScrollBarPolicy
        }
    }
    
    Component {
        id: verticalScrollBar
        
        ScrollBar {    
            flickableItem: root
            orientation: Qt.Vertical
            scrollBarPolicy: root.verticalScrollBarPolicy
        }
    }
    
    Component.onCompleted: {
        horizontalScrollBar.createObject(root);        
        verticalScrollBar.createObject(root);
    }
}
