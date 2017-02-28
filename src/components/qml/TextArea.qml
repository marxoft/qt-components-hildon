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
import "."

/*!
    \class TextArea
    \brief A component for displaying/editing multiple lines of text.
    
    \ingroup components
    
    \include textarea.qml
    
    \sa Label, OssoTextAreaStyle, TextAreaStyle, TextField
*/
FocusScope {
    id: root
    
    /*!
        type:string
        \brief The current text.
    */
    property alias text: textEdit.text
    
    /*!
        \brief The text to be displayed when no text is set.
    */
    property string placeholderText

    /*!
        type:font
        \brief The text font.
    */
    property alias font: textEdit.font
    
    /*!
        type:int
        \brief The current cursor position.
    */
    property alias cursorPosition: textEdit.cursorPosition
    
    /*!
        type:rectangle
        \brief The current cursor rectanle.
    */
    property alias cursorRectangle: textEdit.cursorRectangle
    
    /*!
        \brief The number of lines displayed in the text area.
    */
    property int lineCount
    
    /*!
        \brief The maximum height of a line of text in the text area.
    */
    property int lineHeight
    
    /*!
        type:int
        \brief The painted height of the text area
    */
    property alias paintedHeight: textEdit.paintedHeight
    
    /*!
        type:bool
        \brief Whether the text area is read only.
        
        The default value is \c false.
    */
    property alias readOnly: textEdit.readOnly
    
    /*!
        type:enumeration
        \brief The horizontal alignment of the text.
    */
    property alias horizontalAlignment: textEdit.horizontalAlignment
    
    /*!
        type:enumeration
        \brief The vertical alignment of the text.
    */
    property alias verticalAlignment: textEdit.verticalAlignment
    
    /*!
        type:bool
        \brief Whether text can be selected using the mouse.
        
        The default value is \c true.
    */
    property alias selectByMouse: textEdit.selectByMouse

    /*!
        type:string
        \brief The currently selected text.
    */
    property alias selectedText: textEdit.selectedText
    
    /*!
        type:int
        \brief The cursor position at the start of the currently selected text.
    */
    property alias selectionStart: textEdit.selectionStart
    
    /*!
        type:int
        \brief The cursor position at the end of the currently selected text.
    */
    property alias selectionEnd: textEdit.selectionEnd
    
    /*!
        type:enumeration
        \brief The wrapping behaviour of the text.
    */
    property alias wrapMode: textEdit.wrapMode
    
    /*!
        type:enumeration
        \brief The format of the text.
    */
    property alias textFormat: textEdit.textFormat
    
    /*!
        type:enumeration
        \brief The input method hints.
    */
    property alias inputMethodHints: textEdit.inputMethodHints
    
    /*!
        type:TextAreaStyle
        \brief Provides styling properties for the text area.
    */
    property QtObject style: TextAreaStyle {}
    
    /*!
        \brief Copies the selected text to the clipboard.
    */
    function copy() {
        textEdit.copy()
    }
    
    /*!
        \brief Pastes text from the clipboard into the text area.
    */
    function paste() {
        textEdit.paste()
    }

    /*!
        \brief Cuts the selected text to the clipboard.
    */
    function cut() {
        textEdit.cut()
    }
    
    /*!
        \brief Clears all text.
    */
    function clear() {
        textEdit.text = "";
    }
    
    /*!
        \brief Forces the text area to become the current focus item.
    */
    function forceActiveFocus() {
        textEdit.forceActiveFocus()
    }

    /*!
        \brief Selects the text between \a start and \a end.
        @param type:int start
        @param type:int end
    */
    function select(start, end) {
        textEdit.select(start, end)
    }

    /*!
        \brief Selects all text.
    */
    function selectAll() {
        textEdit.selectAll()
    }

    /*!
        \brief Selects the current word.
    */
    function selectWord() {
        textEdit.selectWord()
    }

    /*!
        \brief Returns the cursor position at co-ordinates \a x, \a y.
        @param type:int x
        @param type:int y
        @return type:point
    */
    function positionAt(x, y) {
        var p = mapToItem(textEdit, x, y);
        return textEdit.positionAt(p.x, p.y)
    }

    /*!
        \brief Returns the position at point \a pos as a rectangle.
        @param type:point pos
        @return type:rect
    */
    function positionToRectangle(pos) {
        var rect = textEdit.positionToRectangle(pos)
        var point = mapFromItem(textEdit, rect.x, rect.y)
        rect.x = point.x; rect.y = point.y
        return rect;
    }
    
    width: style.defaultWidth
    height: Math.max(style.defaultHeight, textEdit.paintedHeight)
    onHeightChanged: textEdit.height = height - style.paddingBottom

    BorderImage {
        id: background

        anchors.fill: parent
        border {
            left: root.style.backgroundCornerMargin
            right: root.style.backgroundCornerMargin
            top: root.style.backgroundCornerMargin
            bottom: root.style.backgroundCornerMargin
        }
        source: !root.enabled ? root.style.backgroundDisabled : textEdit.activeFocus
                ? root.style.backgroundSelected : root.style.background
        smooth: true
    }

    TextEdit {
        id: textEdit
        
        property int lineCount: Math.floor(paintedHeight / lineHeight)
        property int lineHeight: cursorRectangle.height

        anchors {
            left: parent.left
            leftMargin: root.style.paddingLeft
            right: parent.right
            rightMargin: root.style.paddingRight
            top: parent.top
            topMargin: root.style.paddingTop
        }
        color: enabled ? root.style.textColor : platformStyle.reversedDisabledTextColor
        enabled: root.enabled
        selectedTextColor: root.style.selectedTextColor
        selectionColor: root.style.selectionColor
        selectByMouse: true
        wrapMode: Text.WordWrap
        onLineCountChanged: root.lineCount = lineCount
        onLineHeightChanged: root.lineHeight = lineHeight
    
        Loader {
            id: placeholderLoader

            anchors.fill: parent
            sourceComponent: (!textEdit.text) && (root.placeholderText) && (!textEdit.activeFocus)
            ? placeholder : undefined
        }

        MouseArea {
            anchors.fill: parent
            enabled: !root.enabled
        }
    }
    
    Component {
        id: placeholder
        
        Label {
            color: platformStyle.reversedSecondaryTextColor
            wrapMode: textEdit.wrapMode
            text: root.placeholderText
        }
    }
}
