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
    \class SpinBox
    \brief A text field used for choosing an integer value.
    
    \ingroup components
    
    \sa DoubleSpinBox, SpinBoxStyle
*/
FocusScope {
    id: root
    
    /*!
        \brief The minimum value that can be chosen.
        
        The default value is \c 0.
    */
    property int minimum: 0
    
    /*!
        \brief The maximum value that can be chosen.
        
        The default value is \c 99.
    */
    property int maximum: 99
    
    /*!
        \brief The step size used to increment/decrement the value.
        
        The default value is \c 1.
    */
    property int singleStep: 1
    
    /*!
        \brief The current value.
        
        The default value is \c 0.
    */
    property int value
    
    /*!
        \brief The current text, including the prefix and suffix.        
    */
    property string text
    
    /*!
        \type:string
        \brief The current text without the prefix and suffix.        
    */
    property alias cleanText: textInput.text
    
    /*!
        \brief The text to be displayed before the value.
        
        The default value is an empty string.
    */
    property string prefix
    
    /*!
        \brief The text to be displayed after the value.
        
        The default value is an empty string.
    */
    property string suffix
    
    /*!
        \brief Whether incrementing/decrementing the value should wrap once the minimum/maximum is reached.
        
        The default value \c false.
    */
    property bool wrapping: false
    
    /*!
        type:string
        \brief The text to be displayed instead of a numeric value whenever the current value is equal to minimum.
    */
    property alias specialValueText: placeholder.text
    
    property alias inputMethodHints: textInput.inputMethodHints
    property alias font: textInput.font
    property alias readOnly: textInput.readOnly
    
    /*!
        type:SpinBoxStyle
        \brief Provides styling properties for the spin box.
    */
    property QtObject style: SpinBoxStyle {}
    
    /*!
        \brief Emitted when the return key is pressed.
    */
    signal accepted
    
    /*!
        \brief Increments the value.
    */
    function stepUp() {
        if (value <= (maximum - singleStep)) {
            value += singleStep;
        }
        else if (wrapping) {
            value = minimum;
        }
    }
    
    /*!
        \brief Decrements the value.
    */
    function stepDown() {
        if (value >= (minimum + singleStep)) {
            value -= singleStep;
        }
        else if (wrapping) {
            value = maximum;
        }
    }
    
    /*!
        \brief Sets the value to the minimum.
    */
    function clear() {
        value = minimum;
    }
    
    /*!
        \brief Selects the text.
    */
    function selectAll() {
        textInput.selectAll()
    }
    
    /*!
        \brief Forces the spin box to be the current focus item.
    */
    function forceActiveFocus() {
        textInput.forceActiveFocus()
    }
    
    width: style.defaultWidth
    height: 70
    clip: true
    
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
    
    Loader {
        id: prefixLoader
        
        anchors {
            left: parent.left
            leftMargin: root.style.paddingLeft
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: root.style.baselineOffset
        }
        sourceComponent: root.prefix ? prefixLabel : undefined
    }
    
    Loader {
        id: suffixLoader
        
        anchors {
            left: textInput.right
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: root.style.baselineOffset
        }
        sourceComponent: root.suffix ? suffixLabel : undefined
    }
    
    Loader {
        id: placeholderLoader
        
        sourceComponent: (root.value == root.minimum) && (root.specialValueText) ? placeholderLabel : undefined
    }
    
    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onPressed: {
            if (root.enabled) {
                textInput.forceActiveFocus();
                
                if (mouseX < textInput.x) {
                    textInput.cursorPosition = 0;
                }
                else if (mouseX > textInput.x + textInput.width) {
                    textInput.cursorPosition = textInput.text.length;
                }
            }
        }
        onDoubleClicked: if (root.enabled) textInput.selectAll();
    }
    
    TextInput {
        id: textInput

        anchors {
            left: prefixLoader.right
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: root.style.baselineOffset
        }
        color: root.style.textColor
        selectedTextColor: root.style.selectedTextColor
        selectionColor: root.style.selectionColor
        selectByMouse: true
        validator: IntValidator {
            bottom: root.minimum
            top: root.maximum
        }
        
        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Up: {
                root.stepUp();
                root.selectAll();
                break;
            }
            case Qt.Key_Down: {
                root.stepDown();
                root.selectAll();
                break;
            }
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
        
        onTextChanged: {
            var value = parseInt(text);
            
            if (!isNaN(value)) {
                root.value = value;
            }
        }
    }    
    
    Component {
        id: prefixLabel
        
        Label {
            color: textInput.color
            text: root.prefix
        }
    }
    
    Component {
        id: suffixLabel
        
        Label {
            color: textInput.color
            text: root.suffix
        }
    }
    
    Component {
        id: placeholderLabel
        
        Label {
            id: placeholder

            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            color: platformStyle.reversedSecondaryTextColor
        }
    }
    
    onValueChanged: {
        cleanText = value;
        text = prefix + value + suffix;
    }
    
    Component.onCompleted: textInput.text = value
}
