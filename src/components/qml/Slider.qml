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
    
    property int minimum: 0
    property int maximum: 100
    property int value: 0
    property int orientation: Qt.Horizontal
    property bool tracking: false
    property alias pressed: mouseArea.pressed
    
    property QtObject style: SliderStyle {}
        
    width: 250
    height: 60
    rotation: orientation == Qt.Vertical ? -90 : 0
    
    BorderImage {
        id: leftBackground
        
        anchors {
            left: parent.left
            right: handle.left
            top: parent.top
            bottom: parent.bottom
        }
        border {
            left: root.style.backgroundMarginLeft
            right: root.style.backgroundMarginRight
            top: root.style.backgroundMarginTop
            bottom: root.style.backgroundMarginBottom
        }
        smooth: true
        source: root.enabled ? root.style.leftBackground : root.style.leftBackgroundDisabled
    }
    
    BorderImage {
        id: rightBackground
        
        anchors {
            left: handle.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        border {
            left: root.style.backgroundMarginRight
            right: root.style.backgroundMarginLeft
            top: root.style.backgroundMarginTop
            bottom: root.style.backgroundMarginBottom
        }
        smooth: true
        source: root.enabled ? root.style.rightBackground : root.style.rightBackgroundDisabled
    }
    
    Image {
        id: handle
        
        anchors.verticalCenter: parent.verticalCenter
        smooth: true
        source: root.enabled ? root.style.handle : root.style.handleDisabled
    }
    
    MouseArea {
        id: mouseArea
                
        anchors.fill: parent
        drag {
            target: handle
            axis: Drag.XAxis
            minimumX: 0
            maximumX: Math.floor(width - (handle.width / 2))
        }
        onPressed: handle.x = Math.floor(mouseX - (handle.width / 2))
        onReleased: internal.updateValue()
    }
    
    QtObject {
        id: internal
        
        function updateValue() {
            root.value = Math.floor((mouseArea.mouseX / root.width) * (root.maximum - root.minimum));
        }
    }
    
    Binding {
        target: handle
        property: "x"
        value: Math.floor((root.width * root.value) / (root.maximum - root.minimum) - (handle.width / 2))
        when: (!mouseArea.pressed) && (root.value > 0) && (root.maximum > root.minimum)
    }
    
    Connections {
        target: root.tracking ? mouseArea : null
        onMouseXChanged: internal.updateValue()
    }
}
