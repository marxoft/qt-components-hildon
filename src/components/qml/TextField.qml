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
    \class TextField
    \brief A component for displaying/editing a single line of text.
    
    \ingroup components
    
    \include textfield.qml
    
    \sa Label, TextArea, TextFieldStyle
*/
FocusScope {
    id: root
    
    /*!
        type:string
        \brief The current text.
    */
    property alias text: textInput.text
    
    /*!
        type:string
        \brief The text to be displayed when no text is set.
    */
    property alias placeholderText: placeholder.text
    
    /*!
        type:enumeration
        \brief The input method hints
    */
    property alias inputMethodHints: textInput.inputMethodHints
    
    /*!
        type:font
        \brief The text font.
    */
    property alias font: textInput.font
    
    /*!
        type:int
        \brief The current cursor position.
    */
    property alias cursorPosition: textInput.cursorPosition
    
    /*!
        type:int
        \brief The maximum allowed length of the text.
    */
    property alias maximumLength: textInput.maximumLength
    
    /*!
        type:bool
        \brief Whether the text field is read only.
        
        The default value is \c false.
    */
    property alias readOnly: textInput.readOnly
    
    /*!
        type:bool
        \brief Whether the current text passes validation by the validator.
        
        Return tru if no validator is set.
        
        \sa validator
    */
    property alias acceptableInput: textInput.acceptableInput
    
    /*!
        type:enumeration
        \brief The input mask.
    */
    property alias inputMask: textInput.inputMask
    
    /*!
        type:variant
        \brief The validator used to validate the text.
        
        \sa acceptableInput
    */
    property alias validator: textInput.validator
    
    /*!
        type:string
        \brief The currently selected text.
    */
    property alias selectedText: textInput.selectedText
    
    /*!
        type:int
        \brief The cursor position at the start of the currently selected text.
    */
    property alias selectionStart: textInput.selectionStart
    
    /*!
        type:int
        \brief The cursor position at the end of the currently selected text.
    */
    property alias selectionEnd: textInput.selectionEnd
    
    /*!
        type:enumeration
        \brief Specifies how the text should be displayed.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>TextInput.Normal</td>
                <td>Displays the text as it is (Default).</td>
            </tr>
            <tr>
                <td>TextInput.Password</td>
                <td>Displays asterixes instead of characters.</td>
            </tr>
            <tr>
                <td>TextInput.NoEcho</td>
                <td>Displays nothing.</td>
            </tr>
            <tr>
                <td>TextInput.PasswordEchoOnEdit</td>
                <td>Displays characters as they are entered while editing, otherwise displays asterisks.</td>
            </tr>
        </table>
    */
    property alias echoMode: textInput.echoMode
    
    /*!
        type:TextFieldStyle
        \brief Provides styling properties for the text field.
    */
    property QtObject style: TextFieldStyle {}
    
    /*!
        \brief Emitted when the return key is pressed.
    */
    signal accepted
    
    /*!
        \brief Copies the selected text to the clipboard.
    */
    function copy() {
        textInput.copy();
    }
    
    /*!
        \brief Pastes text from the clipboard into the text area.
    */
    function paste() {
        textInput.paste()
    }
    
    /*!
        \brief Cuts the selected text to the clipboard.
    */
    function cut() {
        textInput.cut()
    }
    
    /*!
        \brief Clears all text.
    */
    function clear() {
        textInput.text = "";
    }
    
    /*!
        \brief Selects the text between \a start and \a end.
        @param type:int start
        @param type:int end
    */
    function select(start, end) {
        textInput.select(start, end)
    }
    
    /*!
        \brief Selects all text.
    */
    function selectAll() {
        textInput.selectAll()
    }
    
    /*!
        \brief Selects the current word.
    */
    function selectWord() {
        textInput.selectWord()
    }
    
    /*!
        \brief Returns the cursor position at \a x.
        @param type:int x
        @return type:point
    */
    function positionAt(x) {
        var p = mapToItem(textInput, x, 0);
        return textInput.positionAt(p.x)
    }
    
    /*!
        \brief Returns the position at point \a pos as a rectangle.
        @param type:point pos
        @return type:rect
    */
    function positionToRectangle(pos) {
        var rect = textInput.positionToRectangle(pos)
        rect.x = mapFromItem(textInput, rect.x, 0).x
        return rect;
    }
    
    /*!
        \brief Forces the text field to become the current focus item.
    */
    function forceActiveFocus() {
        textInput.forceActiveFocus()
    }
    
    width: style.defaultWidth
    height: style.defaultHeight
    
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
        selectByMouse: true

        Label {
            id: placeholder

            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            color: platformStyle.reversedSecondaryTextColor
            visible: (textInput.text == "") && (!textInput.activeFocus)
        }
        
        Keys.onEnterPressed: {
            if ((acceptableInput) && (!event.isAutoRepeat)) {
                root.accepted();
                event.accepted = true;
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        enabled: !root.enabled
    }
}
