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

/*!
    \class ScrollDecorator
    \brief Provides a scrolling indicator for a Flickable or ListView.
    
    \ingroup components
    
    \sa Flickable, ListView, ScrollBar
*/
Item {
    id: root
    
    /*!
        \brief The flickable item to which the scroll decorator is attached.
    */
    property Flickable flickableItem
    
    /*
        type:enumeration
        \brief The orientation of the scroll decorator.
        
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
        type:ScrollDecoratorStyle
        \brief Provides styling properties for the scroll decorator.
    */
    property QtObject style: ScrollDecoratorStyle {}
    
    anchors.fill: flickableItem ? flickableItem : undefined
    
    Loader {
        id: loader
        
        anchors.right: parent.right
        sourceComponent: flickableItem ? verticalScrollBar : undefined
    }
    
    Component {
        id: horizontalScrollBar
        
        Rectangle {        
            anchors.bottom: parent.bottom
            x: flickableItem.visibleArea.xPosition * flickableItem.width
            width: flickableItem.visibleArea.widthRatio * flickableItem.width
            height: root.style.scrollBarWidth
            color: root.style.scrollBarColor
            opacity: (flickableItem.movingHorizontally) || (timer.running) ? 1 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 400
                }
            }
        }
    }
    
    Component {
        id: verticalScrollBar
        
        Rectangle {        
            anchors.right: parent.right
            y: flickableItem.visibleArea.yPosition * flickableItem.height
            width: root.style.scrollBarWidth
            height: flickableItem.visibleArea.heightRatio * flickableItem.height
            color: root.style.scrollBarColor
            opacity: (flickableItem.movingVertically) || (timer.running) ? 1 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 400
                }
            }
        }
    }
    
    Timer {
        id: timer
        
        interval: 3000
        running: (flickableItem) && (flickableItem.interactive) && (!flickableItem.movingVertically)
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
                sourceComponent: flickableItem ? horizontalScrollBar : undefined
            }
            
            PropertyChanges {
                target: timer
                running: (flickableItem) && (flickableItem.interactive) && (!flickableItem.movingHorizontally)
            }
        }
    }
}
