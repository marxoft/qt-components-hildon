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
import "."

/*!
    \class TextArea
    \brief A component for displaying/editing multiple lines of text.
    
    \ingroup components
    
    \sa Label, TextAreaStyle, TextField
*/
FocusScope {
    id: root
    
    /*!
        type:string
        \brief The current text.
    */
    property alias text: textEdit.text
    
    /*!
        type:string
        \brief The text to be displayed when no text is set.
    */
    property alias placeholderText: placeholder.text

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
        \brief The number of lines displayed in the text area.
    */
    property int lineCount
    
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
        source: !root.enabled ? root.style.backgroundDisabled : textEdit.activeFocus
                ? root.style.backgroundSelected : root.style.background
        smooth: true
    }
    
    Flickable {
        id: flickable
        
        function ensureVisible(r) {
            if (contentX >= r.x) {
                contentX = r.x;
            }
            else if (contentX + width <= r.x+r.width) {
                contentX = r.x + r.width - width;
            }
            
            if (contentY >= r.y) {
                contentY = r.y;
            }
            else if (contentY + height <= r.y + r.height) {
                contentY = r.y + r.height - height;
            }
        }
        
        anchors {
            fill: parent
            leftMargin: root.style.paddingLeft
            rightMargin: root.style.paddingRight
            topMargin: platformStyle.paddingLarge
            bottomMargin: platformStyle.paddingLarge
        }
        clip: true
        horizontalScrollBarPolicy: contentWidth > width ? Qt.ScrollBarAsNeeded : Qt.ScrollBarAlwaysOff
        contentWidth: textEdit.paintedWidth + platformStyle.paddingLarge
        contentHeight: textEdit.paintedHeight + platformStyle.paddingLarge
        
        TextEdit {
            id: textEdit
            
            property int lineCount: Math.floor(height / lineHeight)
            property int lineHeight: cursorRectangle.height

            width: flickable.width
            color: root.style.textColor
            selectedTextColor: root.style.selectedTextColor
            selectionColor: root.style.selectionColor
            wrapMode: Text.WordWrap
            onCursorRectangleChanged: flickable.ensureVisible(cursorRectangle)
        
            Label {
                id: placeholder

                anchors.fill: parent
                color: platformStyle.reversedSecondaryTextColor
                wrapMode: textEdit.wrapMode
                visible: (textEdit.text == "") && (!textEdit.activeFocus)
            }

            MouseArea {
                anchors.fill: parent
                enabled: !root.enabled
            }
        }
    }
    
    MouseArea {
        anchors.fill: parent
        onPressed: {
            mouse.accepted = false;
            textEdit.forceActiveFocus();
        }
    }
}
