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
import org.hildon.components 1.0
import "."

/*!
    \class ComboBox
    \brief Provides a drop-down list functionality.
    
    \ingroup components
    
    \include combobox.qml
    
    \sa ComboBoxStyle, OssoComboBoxStyle
*/
FocusScope {
    id: root
    
    /*!
        type:int
        \brief The number of items in the combo box.
    */
    property alias count: repeater.count
    
    /*!
        \brief The index of the currently selected item in the combo box.
    */
    property int currentIndex
    
    /*!
        \brief The text of the currently selected item in the combo box.
    */
    property string currentValueText
    
    /*!
        \brief Whether the combo box can be edited by the user.
        
        The default value is \c false.
    */
    property bool editable: false
    
    /*!
        type:string
        \brief The text being manipulated by the user for an editable combo box.
    */
    property alias editText: textInput.text
    
    /*!
        type:enumeration
        \brief The policy used to determine how new strings should be inserted in an editable combo box.
        
        The possible values are:
        
        <table>
            <tr>
                <th>Name</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>InsertPolicy.NoInsert</td>
                <td>The string will not be inserted.</td>
            </tr>
            <tr>
                <td>InsertPolicy.InsertAtTop</td>
                <td>The string will be inserted as the first item.</td>
            </tr>
            <tr>
                <td>InsertPolicy.InsertAtCurrent</td>
                <td>The current item will be replaced.</td>
            </tr>
            <tr>
                <td>InsertPolicy.InsertAtBottom</td>
                <td>The string will be inserted after the last item (default).</td>
            </tr>
            <tr>
                <td>InsertPolicy.InsertAfterCurrent</td>
                <td>The string will be inserted after the current item.</td>
            </tr>
            <tr>
                <td>InsertPolicy.InsertBeforeCurrent</td>
                <td>The string will be inserted before the current item.</td>
            </tr>
            <tr>
                <td>InsertPolicy.InsertAlphabetically</td>
                <td>The string will be inserted in alphabetic order.</td>
            </tr>
        </table>        
    */
    property int insertPolicy: InsertPolicy.InsertAtBottom
    
    /*!
        type:int
        \brief The maximum number of items allowed in the combo box.
        
        The default value is \c Number.MAX_VALUE.
    */
    property real maximumCount: Number.MAX_VALUE
    
    /*!
        type:variant
        \brief The model to populate the combo box from.
        
        The default model is an empty array.
    */
    property alias model: repeater.model
    
    /*!
        type:ComboBoxStyle
        \brief Used to provide styling properties for the combo box.
    */
    property QtObject style: ComboBoxStyle {}
    
    /*!
        \brief The model role used for displaying text the combo box items.
    */
    property string textRole
    
    /*!
        type:Validator
        \brief The text validator for an editable combo box.
    */
    property alias validator: textInput.validator
    
    /*!
        \brief Emitted when the user selects an item in the combo box.
    */
    signal selected(string text)
    
    /*! \brief Returns the text for a given \a index.
        @param type:int index
        @return type:string
        
        If an invalid index is provided, \c null is returned
    */
    function textAt(index) {
        if ((index > -1) && (index < count)) {
            return repeater.itemAt(index).text;
        }
        
        return null;
    }

    /*! \brief Finds and returns the index of a given \a text
        @param type:string text
        @return type:int
        
        If no match is found, \c -1 is returned. The search is case sensitive.
    */
    function findText(text) {
        return textInput.find(text, Qt.MatchExactly);
    }
    
    /*!
        \brief Inserts \a text at the specified \a index.
        @param type:int index
        @param type:string text
        @return type:bool
        
        Returns \c true if \a text is successfully inserted.
        
        \sa insertItems()
    */
    function insertItem(index, text) {
        if (!repeater.model) {
            return false;
        }
        
        if (repeater.modelIsArray) {
            var m = repeater.model;
            m.splice(index, 0, text);
            repeater.model = m;
            return true;
        }
        
        if (repeater.model["insert"]) {
            repeater.model.insert(index, {textRole: text});
            return true;
        }
                
        return false;
    }
    
    /*!
        \brief Inserts \a list at the specified \a index.
        @param type:int index
        @param type:stringlist list
        @return type:bool
        
        Returns \c true if \a list is successfully inserted.
        
        \sa insertItem()
    */
    function insertItems(index, list) {
        for (var i = 0; i < list.length; i++) {
            if (!insertItem(index++, list[i])) {
                return false;
            }
        }
        
        return true;
    }
    
    /*!
        \brief Removes the item at \a index.
        @param type:int index
        @return type:bool
        
        Returns \c true if the item is successfully removed.
    */
    function removeItem(index) {
        if (!repeater.model) {
            return false;
        }
        
        if (repeater.modelIsArray) {
            var m = repeater.model;
            m.splice(index, 1);
            repeater.model = m;
            return true;
        }
        
        if (repeater.model["remove"]) {
            repeater.model.remove(index);
            return true;
        }        
        
        return false;
    }
    
    /*!
        \brief Replaces the item at \a index with \a text.
        @param type:int index
        @param type:string text
        @return type:bool
        
        Returns \c true if the item is successfully replaced.
    */
    function replaceItem(index, text) {
        if (!repeater.model) {
            return false;
        }
        
        if (repeater.modelIsArray) {
            var m = repeater.model;
            m.splice(index, 1, text);
            repeater.model = m;
            return true;
        }
        
        if (repeater.model["setProperty"]) {
            repeater.model.setProperty(index, textRole, text);
            return true;
        }        
        
        return false;
    }
    
    width: style.defaultWidth
    height: style.defaultHeight
    
    BorderImage {
        id: background

        anchors {
            left: parent.left
            right: button.left
            top: parent.top
            bottom: parent.bottom
        }
        border {
            left: root.style.backgroundMarginLeft
            right: root.style.backgroundMarginRight
            top: root.style.backgroundMarginTop
            bottom: root.style.backgroundMarginBottom
        }
        source: root.style.background
        smooth: true
    }
    
    BorderImage {
        id: button

        width: root.style.buttonWidth
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        border {
            left: root.style.backgroundMarginLeft
            right: root.style.backgroundMarginRight
            top: root.style.backgroundMarginTop
            bottom: root.style.backgroundMarginBottom
        }
        source: root.style.button
        smooth: true
        
        Image {
            id: icon
        
            anchors.centerIn: parent
            smooth: true
            source: root.style.icon
        }
        
        MouseArea {
            id: buttonMouseArea
            
            anchors.fill: parent
            enabled: (root.enabled) && (repeater.count)
            onPressed: popup.visible = !popup.visible
        }
    }
        
    TextInput {
        id: textInput
        
        function find(text, searchType) {
            for (var i = 0; i < repeater.count; i++) {
                var currentString = textAt(i);
                
                switch (searchType) {
                case Qt.MatchExactly:
                    if (text == currentString) {
                        return i;
                    }
                    
                    break;
                case Qt.CaseSensitive:
                    if (currentString.indexOf(text) == 0) {
                        return i;
                    }
                    
                    break;
                case Qt.MatchFixedString:
                    if ((currentString.toLowerCase().indexOf(text.toLowerCase()) == 0)
                        && (currentString.length == text.length)) {
                        return i;
                    }
                    
                    break;
                default:
                    if (currentString.toLowerCase().indexOf(text.toLowerCase()) == 0) {
                        return i;
                    }
                    
                    break;
                }
            }
            
            return -1;
        }
        
        anchors {
            left: background.left
            leftMargin: root.style.paddingLeft
            right: background.right
            rightMargin: root.style.paddingRight
            verticalCenter: background.verticalCenter
            verticalCenterOffset: root.style.baselineOffset
        }
        color: root.style.textColor
        enabled: (root.enabled) && (root.editable)
        selectByMouse: true
        
        Keys.forwardTo: flickable
        Keys.onEnterPressed: {
            if ((acceptableInput) && (!event.isAutoRepeat)) {
                var index = find(text, Qt.MatchFixedString);
                
                if (index == -1) {
                    switch (root.insertPolicy) {
                    case InsertPolicy.NoInsert:
                        root.currentIndex = -1;
                        return;
                    case InsertPolicy.InsertAtTop: {
                        if (root.insertItem(0, text)) {
                            root.currentIndex = 0;
                        }
                        else {
                            root.currentIndex = -1;
                            return;
                        }
                        
                        break;
                    }
                    case InsertPolicy.InsertAtCurrent: {
                        if (!root.replaceItem(root.currentIndex, text)) {
                            root.currentIndex = -1;
                            return;
                        }
                        
                        break;
                    }
                    case InsertPolicy.InsertAtBottom: {
                        if (root.insertItem(repeater.count, text)) {
                            root.currentIndex = repeater.count - 1;
                        }
                        else {
                            root.currentIndex = -1;
                            return;
                        }
                        
                        break;
                    }
                    case InsertPolicy.InsetAfterCurrent: {
                        if (root.insertItem(root.currentIndex + 1, text)) {
                            root.currentIndex = root.currentIndex + 1;
                        }
                        else {
                            root.currentIndex = -1;
                            return;
                        }
                        
                        break;
                    }
                    case InsertPolicy.InsertBeforeCurrent: {
                        if (root.insertItem(root.currentIndex - 1, text)) {
                            root.currentIndex = root.currentIndex - 1;
                        }
                        else {
                            root.currentIndex = -1;
                            return;
                        }
                        
                        break;
                    }
                    case InsertPolicy.InsertAlphabetically: {
                        var i = 0;
                        
                        while (i < repeater.count) {
                            if (repeater.itemAt(i).text > text) {
                                break;
                            }
                            
                            i++;
                        }
                        
                        if (root.insertItem(i, text)) {
                            root.currentIndex = i;
                        }
                        else {
                            root.currentIndex = -1;
                            return;
                        }
                        
                        break;
                    }
                    default:
                        root.currentIndex = -1;
                        return;
                    }
                }
                else {
                    root.currentIndex = index;
                }
                
                root.selected(text);
            }
        }
    }
    
    MouseArea {
        id: mouseArea
        
        anchors.fill: background
        enabled: (root.enabled) && ((repeater.count) || (root.editable))
        onPressed: {
            if (textInput.enabled) {
                textInput.forceActiveFocus();
                mouse.accepted = false;
            }
            else {
                popup.visible = !popup.visible;
            }
        }
    }

    Rectangle {
        id: popup
        
        property Item rootItem: findRootItem()
        
        function findRootItem() {
            var p = parent;
            
            while (p.parent != undefined) {
                p = p.parent;
            }
            
            return p;
        }
        
        z: Number.MAX_VALUE
        width: root.width
        visible: false
        color: platformStyle.defaultBackgroundColor    
        border {
            width: 2
            color: platformStyle.disabledTextColor
        }
        
        MouseArea {
            id: popupMouseArea
            
            x: -screen.width
            y: -screen.height
            width: screen.width * 2
            height: screen.height * 2
            onClicked: popup.visible = false
        }
        
        Flickable {
            id: flickable
                                    
            anchors {
                fill: parent
                margins: 1
            }
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            contentHeight: column.height
            style: root.style.listViewStyle
            
            Column {
                id: column
                
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }
                
                Repeater {
                    id: repeater
                    
                    property int currentIndex
                    property bool modelIsArray: true
                                        
                    function itemAt(index) {
                        if ((index > -1) && (index < count)) {
                            return column.children[index];
                        }
                        
                        return null;
                    }
                    
                    model: []
                    
                    BorderImage {
                        property alias text: label.text
                        
                        width: column.width
                        height: root.style.listItemStyle.itemHeight
                        border {
                            left: root.style.listItemStyle.backgroundMarginLeft
                            right: root.style.listItemStyle.backgroundMarginRight
                            top: root.style.listItemStyle.backgroundMarginTop
                            bottom: root.style.listItemStyle.backgroundMarginBottom
                        }
                        smooth: true
                        source: index == repeater.currentIndex ? root.style.listItemStyle.backgroundSelected
                                                               : root.style.listItemStyle.background
                                                               
                        Label {
                            id: label
                            
                            anchors {
                                fill: parent
                                leftMargin: root.style.paddingLeft
                                rightMargin: root.style.paddingRight
                            }
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                            text: root.textRole === "" ?  modelData
                                  : ((repeater.modelIsArray ? modelData[root.textRole] : model[root.textRole]) || "")
                        }
                        
                        MouseArea {
                            anchors.fill: parent
                            onPressed: repeater.currentIndex = index
                            onClicked: {
                                root.currentIndex = index;
                                popup.visible = false;
                                
                                if (!root.editable) {
                                    root.selected(text);
                                }
                            }
                        }
                    }
                    
                    onCurrentIndexChanged: {
                        var item = itemAt(currentIndex);
                        
                        if (item) {
                            if (item.y < flickable.contentY) {
                                flickable.contentY = item.y;
                            }
                            else if ((item.y + item.height) > (flickable.contentY + flickable.height)) {
                                flickable.contentY = item.y + item.height - flickable.height;
                            }
                        }
                    }
                    onModelChanged: modelIsArray = !!model ? model.constructor === Array : false
                }
            }
            
            Keys.onUpPressed: repeater.currentIndex = Math.max(0, repeater.currentIndex - 1)
            Keys.onDownPressed: repeater.currentIndex = Math.min(repeater.count - 1, repeater.currentIndex + 1)
            Keys.onEnterPressed: {
                if (!event.isAutoRepeat) {
                    root.currentIndex = repeater.currentIndex;
                    popup.visible = false;
                    
                    if (!root.editable) {
                        root.selected(root.currentValueText);
                    }
                }
            }
        }
        
        onVisibleChanged: {
            if (visible) {
                parent = rootItem ? rootItem : rootItem = findRootItem();
                var pos = root.mapToItem(rootItem, 0, 0);
                height = Math.min(pos.y, flickable.contentHeight + 2);
                x = pos.x;
                y = pos.y - height;
                repeater.currentIndex = root.currentIndex;
                flickable.forceActiveFocus();
            }
            else {
                parent = root;
                textInput.forceActiveFocus();
            }
        }
    }
        
    StateGroup {
        states: [
            State {
                name: "Disabled"
                when: (!root.editable) && (!root.enabled)
                
                PropertyChanges {
                    target: background
                    source: root.style.backgroundDisabled
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.buttonDisabled
                }
                
                PropertyChanges {
                    target: icon
                    source: root.style.iconDisabled
                }
                
                PropertyChanges {
                    target: textInput
                    color: platformStyle.disabledTextColor
                }
            },
            
            State {
                name: "Editable"
                when: (root.editable) && (root.enabled)
                
                PropertyChanges {
                    target: background
                    source: root.style.textInputBackground
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.textInputButton
                }
                
                PropertyChanges {
                    target: icon
                    source: root.style.textInputIcon
                }
                
                PropertyChanges {
                    target: textInput
                    color: platformStyle.reversedTextColor
                }
            },
            
            State {
                name: "EditableDisabled"
                when: (root.editable) && (!root.enabled)
                
                PropertyChanges {
                    target: background
                    source: root.style.textInputBackgroundDisabled
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.textInputButtonDisabled
                }
                
                PropertyChanges {
                    target: icon
                    source: root.style.textInputIconDisabled
                }
                
                PropertyChanges {
                    target: textInput
                    color: platformStyle.disabledTextColor
                }
            },
            
            State {
                name: "EditableInputFocus"
                when: (root.editable) && (textInput.focus)
                
                PropertyChanges {
                    target: background
                    source: root.style.textInputBackgroundSelected
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.textInputButton
                }
                
                PropertyChanges {
                    target: icon
                    source: root.style.textInputIcon
                }
                
                PropertyChanges {
                    target: textInput
                    color: platformStyle.reversedTextColor
                }
            },
            
            State {
                name: "EditablePressed"
                when: (root.editable) && (buttonMouseArea.pressed)
                
                PropertyChanges {
                    target: background
                    source: root.style.textInputBackground
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.textInputButtonSelected
                }
                
                PropertyChanges {
                    target: icon
                    source: root.style.textInputIconPressed
                }
                
                PropertyChanges {
                    target: textInput
                    color: platformStyle.reversedTextColor
                }
            },
            
            State {
                name: "EditableSelected"
                when: (root.editable) && (popup.visible)
                
                PropertyChanges {
                    target: background
                    source: root.style.textInputBackground
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.textInputButtonSelected
                }
                
                PropertyChanges {
                    target: textInput
                    color: platformStyle.reversedTextColor
                }
            },
            
            State {
                name: "Pressed"
                extend: "Selected"
                when: (!root.editable) && ((mouseArea.pressed) || (buttonMouseArea.pressed))
                
                PropertyChanges {
                    target: icon
                    source: root.style.textInputIcon
                }
            },
            
            State {
                name: "Selected"
                when: (!root.editable) && (popup.visible)
                
                PropertyChanges {
                    target: background
                    source: root.style.background
                }
                
                PropertyChanges {
                    target: button
                    source: root.style.buttonSelected
                }
            }
        ]
    }
    
    QtObject {
        id: internal
        
        property bool complete: false
        
        function updateCurrentText() {
            if (!complete) {
                return;
            }
            
            var text = textAt(root.currentIndex);
            
            if (!text) {
                text = "";
            }
            
            root.currentValueText = text;
            textInput.text = text;
        }
        
        function removeExcessItems() {
            if ((complete) && (repeater.count > root.maximumCount)) {
                root.removeItem(0);
            }
        }
    }
    
    onCountChanged: internal.removeExcessItems();
    onCurrentIndexChanged: internal.updateCurrentText()
    onModelChanged: internal.updateCurrentText()
    onSelected: popup.visible = false
    
    Component.onCompleted: {
        internal.complete = true;
        internal.removeExcessItems();
        internal.updateCurrentText();
    }
}
            
