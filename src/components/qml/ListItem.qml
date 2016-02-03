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

/*!
    \class ListItem
    \brief An item for use as a delegate in a ListView.
    
    \ingroup components
    
    The ListItem component is typically used as a delegate in a ListView. It provides a standard delegate appearance 
    that can be customized using ListItemStyle.
    
    ListItem also handles key events to provide standard key navigation in a ListView. This behaviour can be overriden 
    in ListView.
    
    \sa ListItemStyle, ListView
*/
import QtQuick 1.0
import org.hildon.components 1.0

Item {
    id: root
    
    /*!
        type:bool
        \brief Whether the item is currently pressed
    */
    property alias pressed: mouseArea.pressed
    
    /*!
        type:ListItemStyle
        \brief Provides styling properties for the item.
    */
    property QtObject style: ListItemStyle {}
    
    /*!
        \brief Emitted when the item is clicked or the return key is pressed.
    */
    signal clicked
    
    /*!
        \brief Emitted following a long press on the item.
    */
    signal pressAndHold
    
    width: parent ? parent.width : screen.width
    height: style.itemHeight
    
    BorderImage {
        id: background
        
        anchors.fill: parent
        border {
            left: root.style.backgroundMarginLeft
            right: root.style.backgroundMarginRight
            top: root.style.backgroundMarginTop
            bottom: root.style.backgroundMarginBottom
        }
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
            root.ListView.view.forceActiveFocus();
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
