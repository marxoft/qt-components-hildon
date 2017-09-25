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
    \class MultiListPickSelector
    \brief A pick selector used for selecting an multiple items from a list.
    
    \ingroup components
    
    \snippet selectors.qml MultiListPickSelector
    
    \sa DatePickSelector, TimePickSelector, ValueButton
*/
AbstractPickSelector {
    id: root
    
    /*!
        type:variant
        \brief The model to be used by the view.
    */
    property alias model: repeater.model
    
    /*!
        type:int
        \brief The current number of items in the view.
    */
    property alias count: repeater.count
    
    /*!
        type:list<int>
        \brief The current chosen indexes in the view.
    */
    property variant currentIndexes: []
    
    /*!
        \brief The name of the role that provides the text to be displayed in the delegate.
    */
    property string textRole
    
    /*!
        \brief Selects the item at \a index.
        @param type:int index
    */
    function select(index) {
        if ((index >= 0) && (index < count)) {
            var ci = currentIndexes;
            ci.push(index);
            ci.sort(internal.integerSort);
            currentIndexes = ci;
        }
    }
    
    /*!
        \brief De-selects the item at \a index.
        @param type:int index
    */
    function deselect(index) {
        if ((index >= 0) && (index < count)) {
            var ci = currentIndexes;
            ci.splice(ci.indexOf(index), 1);
            currentIndexes = ci;
        }
    }
    
    height: 360
    currentValueText: qsTr("None chosen")
    
    Flickable {
        id: flickable
                
        anchors {
            left: parent.left
            right: button.left
            rightMargin: platformStyle.paddingMedium
            top: parent.top
            bottom: parent.bottom
        }
        focus: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        contentHeight: column.height
        
        Keys.onUpPressed: repeater.currentIndex = Math.max(0, repeater.currentIndex - 1)
        Keys.onDownPressed: repeater.currentIndex = Math.min(repeater.count - 1, repeater.currentIndex + 1)
        Keys.onEnterPressed: {
            if (!event.isAutoRepeat) {
                if (internal.indexes.indexOf(repeater.currentIndex) == -1) {
                    internal.select(repeater.currentIndex);
                }
                else {
                    internal.select(repeater.currentIndex);
                }
            }
        }
        
        Column {
            id: column
            
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            
            Repeater {
                id: repeater
                
                property int currentIndex: -1
                property bool modelIsArray: false
        
                function itemAt(index) {
                    if ((index >= 0) && (index < count)) {
                        return column.children[index];
                    }
                    
                    return null;
                }
                
                delegate: defaultDelegate
                onModelChanged: modelIsArray = !!model ? model.constructor === Array : false
            }
        }
    }
    
    Button {
        id: button
        
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        style: DialogButtonStyle {}
        text: qsTr("Done")
        onClicked: {
            root.currentIndexes = internal.indexes;
            root.selected(root.currentValueText);
        }
    }
    
    Component {
        id: defaultDelegate
        
        Item {
            id: item
            
            property bool selected: internal.indexes.indexOf(index) != -1
            property alias text: label.text
            
            width: parent.width
            height: 70
            
            BorderImage {
                id: background
                
                anchors.fill: parent
                border {
                    left: 4
                    right: 4
                    top: 4
                    bottom: 4
                }
                smooth: true
                source: "image://theme/TouchListBackground"
                        + ((mouseArea.pressed) || (repeater.currentIndex == index) || (selected)
                        ? "Pressed" : "Normal") 
            }
            
            TextMetrics {
                id: metrics
                
                elideWidth: parent.width - platformStyle.paddingMedium * 2
                            - (selected ? image.width : 0)
                text: root.textRole === "" ?  modelData
                      : ((repeater.modelIsArray ? modelData[root.textRole] : model[root.textRole]) || "")
            }
            
            Label {
                id: label
                
                anchors.centerIn: parent
                text: metrics.elidedText
            }
            
            Image {
                id: image
                
                anchors {
                    right: parent.right
                    rightMargin: platformStyle.paddingMedium
                    verticalCenter: parent.verticalCenter
                }
                source: selected ? "image://icon/widgets_tickmark_list" : ""
            }
            
            MouseArea {
                id: mouseArea
                
                anchors.fill: parent
                onPressed: repeater.currentIndex = index
                onReleased: repeater.currentIndex = -1
                onClicked: selected ? internal.deselect(index) : internal.select(index)
            }
        }
    }
    
    QtObject {
        id: internal
        
        property variant indexes: []
        property bool ready: false
        
        function init() {
            indexes = root.currentIndexes;
            updateValueText();
            ready = true;
        }
        
        function integerSort(a, b) {
            return a - b;
        }
        
        function select(index) {
            var idxs = indexes;
            idxs.push(index);
            idxs.sort(integerSort);
            indexes = idxs;
        }
        
        function deselect(index) {
            var idxs = indexes;
            idxs.splice(idxs.indexOf(index), 1);
            indexes = idxs;
        }
                
        function updateValueText() {
            if (root.currentIndexes.length == 0) {
                root.currentValueText = qsTr("None chosen");
                return;
            }
            
            var vt = [];
            
            for (var i = 0; i < root.currentIndexes.length; i++) {
                var item = repeater.itemAt(root.currentIndexes[i]);
                
                if (item) {
                    vt.push(item.text);
                }
            }
            
            root.currentValueText = vt.join(", ");
        }
    }

    StateGroup {
        id: group

        states: State {
            name: "Portrait"
            when: screen.currentOrientation == Qt.WA_Maemo5PortraitOrientation

            AnchorChanges {
                target: flickable
                anchors.right: parent.right
                anchors.bottom: button.top
            }

            PropertyChanges {
                target: flickable
                anchors.rightMargin: 0
                anchors.bottomMargin: platformStyle.paddingMedium
                clip: true
            }

            PropertyChanges {
                target: button
                width: parent.width
            }

            PropertyChanges {
                target: root
                height: 680
            }
        }
    }
    
    onCurrentIndexesChanged: {
        if (internal.ready) {
            internal.indexes = currentIndexes;
            internal.updateValueText();
        }
    }
    onRejected: internal.indexes = currentIndexes
    onSelected: accept()
    
    Component.onCompleted: internal.init()
}
