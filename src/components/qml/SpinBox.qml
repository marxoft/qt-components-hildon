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
    
    property int minimum: 0
    property int maximum: 99
    property int singleStep: 1
    property int value
    
    property string text
    property string cleanText
    property string prefix
    property string suffix
    
    property bool wrapping: false
    
    property alias specialValueText: placeholder.text
    property alias inputMethodHints: textInput.inputMethodHints
    property alias font: textInput.font
    property alias readOnly: textInput.readOnly
    
    property QtObject style: SpinBoxStyle {}
    
    signal accepted
    
    function stepUp() {
        if (value <= (maximum - singleStep)) {
            value += singleStep;
        }
        else if (wrapping) {
            value = minimum;
        }
    }
    
    function stepDown() {
        if (value >= (minimum + singleStep)) {
            value -= singleStep;
        }
        else if (wrapping) {
            value = maximum;
        }
    }
    
    function clear() {
        value = minimum;
    }
    
    function selectAll() {
        textInput.selectAll()
    }

    function forceActiveFocus() {
        textInput.forceActiveFocus()
    }
    
    width: style.defaultWidth
    height: 70
    
    BorderImage {
        id: background

        anchors.fill: parent
        border {
            left: root.style.backgroundCornerMargin
            right: root.style.backgroundCornerMargin
            top: root.style.backgroundCornerMargin
            bottom: root.style.backgroundCornerMargin
        }
        source: !root.enabled ? root.style.backgroundDisabled : textInput.activeFocus
                ? root.style.backgroundSelected : root.style.background
        smooth: true
    }
    
    TextInput {
        id: textInput

        anchors {
            left: parent.left
            leftMargin: root.style.paddingLeft
            right: parent.right
            rightMargin: root.style.paddingRight
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: root.style.baselineOffset
        }
        color: root.style.textColor
        selectedTextColor: root.style.selectedTextColor
        selectionColor: root.style.selectionColor
        text: root.prefix + root.value + root.suffix
        validator: IntValidator {
            bottom: root.minimum
            top: root.maximum
        }

        Label {
            id: placeholder

            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            color: platformStyle.reversedSecondaryTextColor
            visible: (root.value == root.minimum) && (text != "")
        }
        
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Up:
                root.stepUp();
                break;
            case Qt.Key_Down:
                root.stepDown();
                break;
            case Qt.Key_Enter:
                if ((acceptableInput) && (!event.isAutoRepeat)) {
                    root.accepted();
                }
                
                break;
            default:
                return;
            }
            
            event.accepted = true;
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        enabled: !root.enabled
    }
    
    onValueChanged: {
        selectAll();
        cleanText = value.toString();
        text = textInput.text;
    }
}
