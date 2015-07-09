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

FocusScope {
    id: root
    
    property bool autoRepeat: true
    property bool checkable: false
    property bool checked: false
    property string iconName
    property string iconSource
    property alias pressed: mouseArea.pressed
    property string text
    
    signal clicked
    signal pressAndHold    
    
    MouseArea {
        id: mouseArea
        
        anchors.fill: parent
        enabled: root.enabled
        onClicked: {
            if (root.checkable) {
                root.checked = !root.checked;
            }
            
            root.clicked();
        }
        onPressAndHold: root.pressAndHold()
    }
    
    Keys.onEnterPressed: {
        if ((autoRepeat) || (!event.isAutoRepeat)) {
            if (checkable) {
                checked = !root.checked;
            }
            
            clicked();
            event.accepted = true;
        }
    }
    
    onCheckableChanged: if (!checkable) checked = false;
}
