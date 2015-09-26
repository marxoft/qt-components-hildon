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

/*!
    \class ScrollBar
    \brief Provides a scrolling indicator for a Flickable or ListView.
    
    \ingroup components
    
    \sa Flickable, ListView
*/
Item {
    id: root
    
    /*!
        \brief The flickable item to which the scroll bar is attached.
    */
    property Flickable flickableItem
    
    /*
        type:Qt.Orientation
        \brief The orientation of the scroll bar.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.Horizontal</td>
                <td>Horizontal orientation.</td>
            </tr>
            <tr>
                <td>Qt.Vertical</td>
                <td>Vertical orientation (default).</td>
            </tr>
        </table>        
    */
    property int orientation: Qt.Vertical
    
    /*!
        type:Qt.ScrollBarPolicy
        \brief The policy used to determine whether the scroll bar should be visible.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.ScrollBarAlwaysOn</td>
                <td>The scroll bar should always be visible.</td>
            </tr>
            <tr>
                <td>Qt.ScrollBarAlwaysOff</td>
                <td>The scroll bar should never be visible.</td>
            </tr>
            <tr>
                <td>Qt.ScrollBarAsNeeded</td>
                <td>The scroll bar should be visible when required (default).</td>
            </tr>
        </table>
    */
    property int scrollBarPolicy: Qt.ScrollBarAsNeeded
    
    /*!
        type:ScrollBarStyle
        \brief Provides styling properties for the scroll bar.
    */
    property QtObject style: ScrollBarStyle {}
    
    anchors.fill: flickableItem ? flickableItem : undefined
    
    Loader {
        id: loader
        
        anchors.right: parent.right
        sourceComponent: (!flickableItem) || (root.scrollBarPolicy == Qt.ScrollBarAlwaysOff) ? undefined
                         : verticalScrollBar
    }
    
    Component {
        id: horizontalScrollBar
        
        Rectangle {        
            anchors.bottom: parent.bottom
            x: flickableItem.visibleArea.xPosition * flickableItem.width
            width: flickableItem.visibleArea.widthRatio * flickableItem.width
            height: root.style.scrollBarWidth
            color: root.style.scrollBarColor
            opacity: (root.scrollBarPolicy == Qt.ScrollBarAlwaysOn) || (flickableItem.movingHorizontally)
                     || (timer.running) ? 1 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 250
                }
            }
        }
    }
    
    Component {
        id: verticalScrollBar
        
        Rectangle {
            id: scrollBar
        
            anchors.right: parent.right
            y: flickableItem.visibleArea.yPosition * flickableItem.height
            width: root.style.scrollBarWidth
            height: flickableItem.visibleArea.heightRatio * flickableItem.height
            color: root.style.scrollBarColor
            opacity: (root.scrollBarPolicy == Qt.ScrollBarAlwaysOn) || (flickableItem.movingVertically)
                     || (timer.running) ? 1 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 250
                }
            }
        }
    }
    
    Timer {
        id: timer
        
        interval: 3000
        running: (flickableItem) && (flickableItem.interactive) && (root.scrollBarPolicy == Qt.ScrollBarAsNeeded)
                 && (!flickableItem.movingVertically)
    }
    
    StateGroup {
        states: State {
            name: "Horizontal"
            when: root.orientation == Qt.Horizontal
            
            AnchorChanges {
                target: loader
                anchors {
                    right: undefined
                    bottom: parent.bottom
                }
            }
        
            PropertyChanges {
                target: loader
                sourceComponent: (!flickableItem) || (root.scrollBarPolicy == Qt.ScrollBarAlwaysOff) ? undefined
                                 : horizontalScrollBar
            }
            
            PropertyChanges {
                target: timer
                running: (flickableItem) && (flickableItem.interactive) && (root.scrollBarPolicy == Qt.ScrollBarAsNeeded)
                         && (!flickableItem.movingHorizontally)
            }
        }
    }
}
