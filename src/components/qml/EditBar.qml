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
    
    default property alias buttons: buttonRow.data
    
    /*!
        type:string
        \brief The text to be displayed in the edit bar.
    */
    property alias text: label.text
        
    /*!
        \brief This signal can be emitted when the user clicks the button that confirms the edit action.
    */
    signal accepted
    
    /*!
        \brief This signal can be emitted when the user rejects the edit action.
        
        This signal is also emitted when the 'back' button is pressed.
    */
    signal rejected
    
    /*!
        \fn void EditBar::addButton(Button button)
        \brief Adds the specified \a button to the edit bar.
        @param button
    */
    
    /*!
        \fn Button EditBar::addButton(string text)
        \brief Adds a button width the specified \a text to the edit bar and returns it.
        @param text
        @return button
    */
    
    function addButton() {
        if (Qt.isQtObject(arguments[0])) {
            arguments[0].style = editButtonStyle;
            buttonRow.addItem(arguments[0]);
        }
        else {
            var button = buttonComponent.createObject(buttonRow);
            
            if (typeof arguments[0] === "string") {
                button.text = arguments[0];
            }
            
            return button;
        }
    }
    
    /*!
        \brief Returns the button at the specified \a index, or \c null if \a index is out of range.
        @param type:int index
        @return type:Button
    */
    function button(index) {
        return buttonRow.itemAt(index);
    }
    
    /*!
        \fn void EditBar::insertButton(int index, Button button)
        \brief Inserts the specified \a button into the edit bar at \a index.
        \param index
        \param button
    */
    
    /*!
        \fn Button EditBar::insertButton(int index, string text)
        \brief Inserts a button width the specified \a text into the edit bar at \a index and returns it.
        \param index
        \param text
    */
    
    function insertButton() {
        if (Qt.isQtObject(arguments[1])) {
            arguments[1].style = editButtonStyle;
            buttonRow.insertItem(arguments[0], arguments[1]);
        }
        else {
            var button = buttonComponent.createObject(null);
            
            if (typeof arguments[1] === "string") {
                button.text = arguments[1];
            }
            
            buttonRow.insertItem(arguments[0], button);
            return button;
        }
    }
    
    /*!
        \brief Removes the specified \a button from the edit bar and sets its parent to \c null.
        @param type:Button button
    */
    function removeButton(button) {
        buttonRow.removeItem(button);
    }
    
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
    
    RowLayout {
        id: buttonRow            
        
        anchors {
            right: separator.left
            rightMargin: platformStyle.paddingLarge
            verticalCenter: parent.verticalCenter
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
    
    Component {
        id: buttonComponent
        
        Button {
            style: editButtonStyle
        }
    }
    
    Component.onCompleted: {
        for (var i = 0; i < buttonRow.children.length; i++) {
            var child = buttonRow.children[i];
            
            if (child.hasOwnProperty("style")) {
                child.style = editButtonStyle;
            }
        }
    }
}
