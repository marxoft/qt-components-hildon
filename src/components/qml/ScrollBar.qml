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

Item {
    id: root
    
    property Flickable flickableItem
    property int orientation: Qt.Vertical
    property int scrollBarPolicy: Qt.ScrollBarAsNeeded
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
