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
    
    property alias pressed: mouseArea.pressed
    property Style style: ListItemStyle {}
    
    signal clicked
    signal pressAndHold
    
    width: ListView.view ? ListView.view.width : screen.width
    height: style.itemHeight
    
    Image {
        id: background
        
        anchors.fill: parent
        smooth: true
        source: mouseArea.pressed ? root.style.backgroundPressed :
                (root.ListView.isCurrentItem) && (root.ListView.view.navigationMode == NavigationMode.KeyNavigation)
                ? root.style.backgroundSelected : root.style.background
    }
    
    MouseArea {
        id: mouseArea
        
        z: -1
        anchors.fill: parent
        enabled: root.enabled
        onPressed: {
            root.ListView.view.navigationMode = NavigationMode.TouchNavigation;
            root.ListView.view.currentIndex = index;
        }
        
        onClicked: root.clicked()
        onPressAndHold: root.pressAndHold()
    }
    
    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Enter: {
            if (!event.isAutoRepeat) {
                if (ListView.view.navigationMode != NavigationMode.KeyNavigation) {
                    ListView.view.navigationMode = NavigationMode.KeyNavigation;
                }
                else {
                    ListView.view.currentIndex = index;
                    clicked();
                }
            }
            
            break;
        }
        case Qt.Key_Up: {
            if (ListView.view.orientation == ListView.Vertical) {
                if (ListView.view.navigationMode != NavigationMode.KeyNavigation) {
                    ListView.view.navigationMode = NavigationMode.KeyNavigation;
                }
                else {
                    ListView.view.decrementCurrentIndex();
                }
            }
            
            break;
        }
        case Qt.Key_Down: {
            if (ListView.view.orientation == ListView.Vertical) {
                if (ListView.view.navigationMode != NavigationMode.KeyNavigation) {
                    ListView.view.navigationMode = NavigationMode.KeyNavigation;
                }
                else {
                    ListView.view.incrementCurrentIndex();
                }
            }
            
            break;
        }
        case Qt.Key_Left: {
            if (ListView.view.orientation == ListView.Horizontal) {
                if (ListView.view.navigationMode != NavigationMode.KeyNavigation) {
                    ListView.view.navigationMode = NavigationMode.KeyNavigation;
                }
                else {
                    ListView.view.decrementCurrentIndex();
                }
            }
            
            break;
        }
        case Qt.Key_Right: {
            if (ListView.view.orientation == ListView.Horizontal) {
                if (ListView.view.navigationMode != NavigationMode.KeyNavigation) {
                    ListView.view.navigationMode = NavigationMode.KeyNavigation;
                }
                else {
                    ListView.view.incrementCurrentIndex();
                }
            }
            
            break;
        }
        default:
            event.accepted = false;
            return;
        }
        
        event.accepted = true;
    }
}
