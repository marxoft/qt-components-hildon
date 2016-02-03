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
    \class ScrollBar
    \brief Provides an interactive scroll bar for a Flickable or ListView.
    
    \ingroup components
    
    \sa Flickable, ListView, ScrollDecorator
*/
Item {
    id: root
    
    /*!
        \brief The flickable item to which the scroll bar is attached.
    */
    property Flickable flickableItem
        
    /*
        type:enumeration
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
        \brief The page step size.
        
        The default value is dependent on the size of flickableItem.
    */
    property int pageStep: flickableItem.height
    
    /*!
        \brief The single step size.
        
        The default value is \c 28.
    */
    property int singleStep: 28
    
    /*!
        \brief The minimum value of the scroll bar.
        
        The default value is \c 0.
    */
    property int minimum: 0
    
    /*!
        \brief The maximum value of the scroll bar.
        
        The default value is dependent on the content size of flickableItem.
    */
    property int maximum: flickableItem.contentHeight - flickableItem.height
    
    /*!
        \brief The current value of the scroll bar.
        
        The default value is \c 0.
    */
    property int value: flickableItem.contentY
    
    /*!
        type:bool
        \brief Whether the scroll bar handle is pressed.
    */
    property alias pressed: handleMouseArea.pressed
    
    /*!
        type:ScrollBarStyle
        \brief Provides styling properties for the scroll bar.
    */
    property QtObject style: ScrollBarStyle {}
    
    /*!
        \brief Increases the value by pageStep.
    */
    function pageStepAdd() {
        if (orientation == Qt.Horizontal) {
            flickableItem.contentX = Math.min(maximum, flickableItem.contentX + pageStep);
        }
        else {
            flickableItem.contentY = Math.min(maximum, flickableItem.contentY + pageStep)
        }
    }
    
    /*!
        \brief Decreases the value by pageStep.
    */
    function pageStepSub() {
        if (orientation == Qt.Horizontal) {
            flickableItem.contentX = Math.max(minimum, flickableItem.contentX - pageStep);
        }
        else {
            flickableItem.contentY = Math.max(minimum, flickableItem.contentY - pageStep)
        }
    }
    
    /*!
        \brief Increases the value by singleStep.
    */
    function singleStepAdd() {
        if (orientation == Qt.Horizontal) {
            flickableItem.contentX = Math.min(maximum, flickableItem.contentX + singleStep);
        }
        else {
            flickableItem.contentY = Math.min(maximum, flickableItem.contentY + singleStep)
        }
    }
    
    /*!
        \brief Decreases the value by singleStep.
    */
    function singleStepSub() {
        if (orientation == Qt.Horizontal) {
            flickableItem.contentX = Math.max(minimum, flickableItem.contentX - singleStep);
        }
        else {
            flickableItem.contentY = Math.max(minimum, flickableItem.contentY - singleStep)
        }
    }
    
    anchors.fill: flickableItem
        
    BorderImage {
        id: shaft
        
        anchors {
            right: root.right
            top: root.top
        }
        z: 1000
        height: root.height
        width: root.style.scrollBarWidth
        border {
            left: root.style.shaftMarginLeft
            right: root.style.shaftMarginRight
            top: root.style.shaftMarginTop
            bottom: root.style.shaftMarginBottom
        }
        source: root.enabled ? root.style.shaft : root.style.shaftDisabled
        smooth: true
                
        Item {
            id: handleContainer
            
            anchors {
                left: parent.left
                right: parent.right
                top: subButton.bottom
                bottom: addButton.top
            }
            
            MouseArea {
                id: shaftMouseArea
                
                property bool add: false
            
                anchors.fill: parent
                enabled: root.enabled
                onPressed: {
                    add = mouseY > handle.y + handle.height;
                    
                    if (add) {
                        pageStepAdd();
                    }
                    else {
                        pageStepSub();
                    }
                }
            }
        
            BorderImage {
                id: handle
                            
                width: handleContainer.width
                height: flickableItem.visibleArea.heightRatio * handleContainer.height
                border {
                    left: root.style.handleMarginLeft
                    right: root.style.handleMarginRight
                    top: root.style.handleMarginTop
                    bottom: root.style.handleMarginBottom
                }
                source: handleMouseArea.pressed ? root.style.handlePressed : handleMouseArea.enabled ? root.style.handle
                        : root.style.handleDisabled
                smooth: true
            
                MouseArea {
                    id: handleMouseArea
                
                    width: parent.width
                    height: parent.height
                    enabled: root.enabled
                    drag {
                        target: handle
                        axis: Drag.YAxis
                        minimumY: 0
                        maximumY: handleContainer.height - handle.height
                    }
                }
            }
        }
        
        Image {
            id: subButton
            
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            source: subButtonMouseArea.pressed ? root.style.subButtonPressed : subButtonMouseArea.enabled
                    ? root.style.subButton : root.style.subButtonDisabled
            smooth: true
            
            MouseArea {
                id: subButtonMouseArea
                
                anchors.fill: parent
                enabled: (root.enabled) && (root.value > 0)
                onPressed: singleStepSub()
            }
        }        
        
        Image {
            id: addButton
            
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            source: addButtonMouseArea.pressed ? root.style.addButtonPressed
                    : addButtonMouseArea.enabled ? root.style.addButton : root.style.addButtonDisabled
            smooth: true
            
            MouseArea {
                id: addButtonMouseArea
                
                anchors.fill: parent
                enabled: (root.enabled) && (root.value < root.maximum)
                onPressed: singleStepAdd()
            }
        }
    }
    
    Timer {
        id: timer
        
        interval: 100
        repeat: true
        running: (shaftMouseArea.pressed) || (subButtonMouseArea.pressed) || (addButtonMouseArea.pressed)
        onTriggered: {
            if (shaftMouseArea.pressed) {
                if (shaftMouseArea.add) {
                    pageStepAdd();
                }
                else {
                    pageStepSub();
                }
            }
            else if (subButtonMouseArea.pressed) {
                singleStepSub();
            }
            else if (addButtonMouseArea.pressed) {
                singleStepAdd();
            }
        }
    }
    
    Binding {
        id: handleBinding
        
        target: handle
        property: "y"
        value: flickableItem.visibleArea.yPosition * handleContainer.height
        when: !handleMouseArea.pressed
    }
    
    Binding {
        id: handlePressedBinding
        
        target: flickableItem
        property: "contentY"
        value: handle.y / (handleContainer.height - handle.height) * root.maximum
        when: handleMouseArea.pressed
    }
    
    StateGroup {
        states: State {
            name: "Horizontal"
            when: root.orientation == Qt.Horizontal
            
            PropertyChanges {
                target: root
                maximum: flickableItem.contentWidth - flickableItem.width
            }
            
            PropertyChanges {
                target: root
                value: flickableItem.contentX
            }
            
            PropertyChanges {
                target: shaft
                rotation: -90
                height: root.width
                anchors {
                    rightMargin: Math.floor(height / 2 - width / 2)
                    topMargin: Math.floor(width / 2)
                }
            }
            
            PropertyChanges {
                target: handle
                height: flickableItem.visibleArea.widthRatio * handleContainer.height
            }
            
            PropertyChanges {
                target: handleBinding
                value: flickableItem.visibleArea.xPosition * handleContainer.height
            }
            
            PropertyChanges {
                target: handlePressedBinding
                property: "contentX"
            }
        }
    }
}
