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
    \class AbstractButton
    \brief The base class for buttons.
    
    \ingroup components
    
    AbstractButton provides functions, properties and signals common to interactive buttons. It does not draw any 
    content.
    
    \include buttons.qml    
*/
FocusScope {
    id: root
    
    /*!
        \brief The Action associated with the button.

        The default value is \c null.

        \sa Action
    */
    property Action action
    
    /*!
        \brief Whether the button should grab focus when pressed.
        
        The default value is \c true.
    */
    property bool activeFocusOnPress: true
    
    /*!
        type:bool
        \brief Whether the button should accept auto-repeated key events.
    
        The default value is \c true.
    */
    property alias autoRepeat: defaultAction.autoRepeat
    
    /*!
        \brief Whether the button is checkable.
    
        The default value is \c false.
    */
    property bool checkable: false
    
    /*!
        \brief Whether the button is checked.
    
        The default value is \c false.
    */
    property bool checked: false
    
    /*!
        \brief The ExclusiveGroup to which the button belongs.
    
        The default value is \c null.
    
        \sa ExclusiveGroup
    */
    property ExclusiveGroup exclusiveGroup
    
    /*!
        \brief The name of the icon to be used.
    
        \sa iconSource
    */
    property string iconName
    
    /*!
        \brief The source of the icon to be used.
    
        \sa iconName
    */
    property string iconSource
    
    /*!
        type:bool
        \brief Whether the button is pressed.
    
        The default value is \c false.
    */
    property alias pressed: mouseArea.pressed
    
    /*!
        type:keysequence
        \brief The keyboard shorcut used to click the button.
    */
    property alias shortcut: defaultAction.shortcut
    
    /*!
        \brief The text to be displayed in the button.
    */
    property string text
    
    /*!
        \brief Emitted when the button is clicked.
    */
    signal clicked
    
    /*!
        \brief Emitted when the button \link checked\endlink property is changed.
    */
    signal toggled(bool checked)
    
    Action {
        id: defaultAction
        
        function update(restore) {
            if (!complete) {
                return;
            }
            
            if (action) {
                if (!ownIcon) {
                    root.iconName = action.iconName;
                    root.iconSource = action.iconSource;
                }
                
                if (!ownText) {
                    root.text = action.text;
                }
                
                root.checkable = action.checkable;
                root.checked = action.checked;
                root.enabled = action.enabled;
                root.visible = action.visible;
            }
            else if (restore) {
                root.checkable = checkable;
                root.checked = checked;
                root.enabled = enabled;
                root.iconName = iconName;
                root.iconSource = iconSource;
                root.text = text;
                root.visible = visible;
            }
        }
        
        property bool complete: false
        property bool ownText: false
        property bool ownIcon: false
        
        onTriggered: if (!root.action) root.clicked();
    }
    
    MouseArea {
        id: mouseArea
        
        anchors.fill: parent
        enabled: root.enabled
        onPressed: if (root.activeFocusOnPress) root.forceActiveFocus();
        onClicked: action ? action.trigger() : defaultAction.trigger()
    }
    
    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Space:
        case Qt.Key_Enter:
            break;
        default:
            return;
        }
        
        if ((!event.autoRepeat) || (autoRepeat)) {
            if (action) {
                action.trigger();
            }
            else {
                defaultAction.trigger();
            }
            
            event.accepted = true;
        }
    }
    
    Connections {
        target: action
        onCheckableChanged: root.checkable = action.checkable
        onCheckedChanged: root.checked = action.checked
        onEnabledChanged: root.enabled = action.enabled
        onIconNameChanged: if (!defaultAction.ownIcon) root.iconName = action.iconName;
        onIconSourceChanged: if (!defaultAction.ownIcon) root.iconSource = action.iconSource;
        onTextChanged: if (!defaultAction.ownText) root.text = action.text;
        onVisibleChanged: root.visible = action.visible
    }
    
    onActionChanged: defaultAction.update(true)
    onCheckableChanged: if (!action) defaultAction.checkable = checked;
    onCheckedChanged: {
        if (!action) {
            defaultAction.checked = checked;
        }
        
        toggled(checked);
    }        
    onClicked: if ((checkable) && ((!checked) || (!exclusiveGroup))) checked = !checked;
    onEnabledChanged: if (!action) defaultAction.enabled = enabled;
    onExclusiveGroupChanged: if (exclusiveGroup) exclusiveGroup.addCheckable(root);
    onIconNameChanged: {
        if ((!action) || (iconName != action.iconName)) {
            defaultAction.iconName = iconName;
            defaultAction.ownIcon = true;
        }
    }
    onIconSourceChanged: {
        if ((!action) || (iconSource != action.iconSource)) {
            defaultAction.iconSource = iconSource;
            defaultAction.ownIcon = true;
        }
    }
    onTextChanged: {
        if ((!action) || (text != action.text)) {
            defaultAction.text = text;
            defaultAction.ownText = true;
        }
    }
    onVisibleChanged: if (!action) defaultAction.visible = visible;
    Component.onCompleted: {
        defaultAction.complete = true;
        defaultAction.update(false);
    }
}
