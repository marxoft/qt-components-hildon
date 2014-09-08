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

ListItem {
    id: root

    width: view.width
    height: 70
    
    ListItemImage {
        id: highlight

        anchors.fill: parent
        source: "image://theme/TouchListBackground" + (isCurrentItem ? "Pressed" : "Normal")

    }

    ListItemImage {
        id: icon

        width: 48
        height: 48
        anchors {
            left: parent.left
            leftMargin: platformStyle.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        source: modelData.icon
        smooth: true
    }
    
    ListItemImage {
        id: indicator

        width: 48
        height: 48
        anchors {
            right: parent.right
            rightMargin: platformStyle.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        source: "/usr/share/icons/hicolor/48x48/hildon/general_forward.png"
        smooth: true
    }
    
    ListItemLabel {
        id: name
        
        anchors {
            left: icon.right
            right: indicator.left
            top: parent.top
            bottom: parent.bottom
            margins: platformStyle.paddingMedium
        }
        font.bold: true
        alignment: Qt.AlignVCenter
        text: modelData.name
    }
}
