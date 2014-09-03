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
import "Utils.js" as Utils

ListItem {
    id: root

    width: view.width
    height: 100
    
    ListItemImage {
        id: highlight

        anchors.fill: parent
        source: "/etc/hildon/theme/images/TouchListBackground" + (isCurrentItem ? "Pressed" : "Normal") + ".png"
    }

    ListItemImage {
        id: icon

        width: 78
        height: 78
        anchors {
            left: parent.left
            leftMargin: platformStyle.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        source: modelData["Video:LastPlayedFrame"]
        smooth: true
    }
    
    ListItemRectangle {
        id: rect
            
        height: 24
        anchors {
            left: icon.left
            right: icon.right
            bottom: icon.bottom
        }
        opacity: 0.7
    }
    
    ListItemText {
        id: duration
            
        anchors.fill: rect
        font.pixelSize: platformStyle.fontSizeSmall
        alignment: Qt.AlignCenter
        text: Utils.durationFromSecs(modelData["Video:Duration"])
    }
    
    ListItemText {
        id: title
        
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: icon.right
            right: parent.right
            margins: platformStyle.paddingMedium
        }
        alignment: Qt.AlignCenter
        text: modelData["Video:Title"]
    }
}
