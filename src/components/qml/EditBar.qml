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
import org.hildon.components 1.0

Item {
    id: root
    
    property alias text: label.text
    property alias buttons: buttonRow.children
    
    signal rejected
    
    z: 1000
    width: screen.width
    height: 56
    
    EditButtonStyle {
        id: editButtonStyle
    }
    
    MouseArea {
        anchors.fill: parent
    }
    
    Image {
        id: background
        
        anchors.fill: parent
        smooth: true
        source: "image://theme/wmTitleBar"
    }
    
    Label {
        id: label
        
        anchors {
            left: parent.left
            leftMargin: platformStyle.paddingLarge
            right: buttonRow.left
            rightMargin: platformStyle.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        elide: Text.ElideRight
    }
    
    Row {
        id: buttonRow            
        
        anchors {
            right: separator.left
            rightMargin: platformStyle.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        onChildrenChanged: {
            var child = children[children.length - 1];
            
            if (child.hasOwnProperty("style")) {
                child.style = editButtonStyle;
            }
        }
    }
    
    Image {
        id: separator
        
        anchors {
            right: backButton.left
            verticalCenter: parent.verticalCenter
        }
        smooth: true
        source: "image://theme/wmSeparator"
    }
    
    Button {
        id: backButton
        
        anchors {
            right: parent.right
            top: parent.top
        }
        style: ButtonStyle {
            background: "image://theme/wmButtonRightHalf"
            backgroundPressed: "image://theme/wmButtonRightHalfPressed"
            buttonWidth: screen.currentOrientation == Qt.WA_Maemo5PortraitOrientation ? 70 : 112
            buttonHeight: 56
            iconWidth: 112
            iconHeight: 56
        }
        iconSource: "image://theme/wmBackIcon" + (pressed ? "Pressed" : "")
        onClicked: root.rejected()
    }
}
