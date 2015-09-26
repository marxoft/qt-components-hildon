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

/*!
    \class EditBar
    \brief Provides a container for Button used for confirming edit actions inside a Window.
    
    \brief components
    
    The EditBar component is intended for use inside a Window in fullscreen mode, in place of the status area.
    
    \sa Button, EditButtonStyle, Window
*/
Item {
    id: root
    
    /*!
        type:string
        \brief The text to be displayed in the edit bar.
    */
    property alias text: label.text
    
    /*!
        type:list<Button>
        \brief One or more buttons to be displayed in the edit bar.
        
        When a button is added, it will automatically be styled to suit the edit bar.
    */
    property alias buttons: buttonRow.children
    
    /*!
        \brief This signal can be emitted when the user clicks the button that confirms the edit action.
    */
    signal accepted
    
    /*!
        \brief This signal can be emitted when the user rejects the edit action.
        
        This signal is also emitted when the 'back' button is pressed.
    */
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
