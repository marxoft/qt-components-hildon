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

FocusScope {
    id: root
    
    property alias text: textEdit.text
    property alias placeholderText: placeholder.text

    property alias font: textEdit.font
    property alias cursorPosition: textEdit.cursorPosition
    property alias readOnly: textEdit.readOnly

    property alias horizontalAlignment: textEdit.horizontalAlignment
    property alias verticalAlignment: textEdit.verticalAlignment

    property alias selectedText: textEdit.selectedText
    property alias selectionStart: textEdit.selectionStart
    property alias selectionEnd: textEdit.selectionEnd

    property alias wrapMode: textEdit.wrapMode
    property alias textFormat: textEdit.textFormat
    
    property alias inputMethodHints: textEdit.inputMethodHints
    
    property TextAreaStyle style: TextAreaStyle {}
        
    function copy() {
        textEdit.copy()
    }

    function paste() {
        textEdit.paste()
    }

    function cut() {
        textEdit.cut()
    }
    
    function clear() {
        textEdit.text = "";
    }

    function forceActiveFocus() {
        textEdit.forceActiveFocus()
    }

    function select(start, end) {
        textEdit.select(start, end)
    }

    function selectAll() {
        textEdit.selectAll()
    }

    function selectWord() {
        textEdit.selectWord()
    }

    function positionAt(x, y) {
        var p = mapToItem(textEdit, x, y);
        return textEdit.positionAt(p.x, p.y)
    }

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
        
        anchors {
            fill: parent
            leftMargin: root.style.paddingLeft
            rightMargin: root.style.paddingRight
            topMargin: platformStyle.paddingLarge
            bottomMargin: platformStyle.paddingLarge
        }
        clip: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        contentHeight: textEdit.height + platformStyle.paddingLarge
        
        TextEdit {
            id: textEdit

            height: paintedHeight
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            color: root.style.textColor
            selectedTextColor: root.style.selectedTextColor
            selectionColor: root.style.selectionColor
            wrapMode: Text.WordWrap
            onCursorPositionChanged: flickable.contentY = Math.max(0, cursorRectangle.y + cursorRectangle.height
                                                                   - flickable.height)
        
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
}
