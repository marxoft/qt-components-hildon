/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

import org.hildon.components 1.0

Page {
    id: root

    windowTitle: qsTr("Edit")
    fullScreen: true

    EditBar {
        id: editBar

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        text: qsTr("Choose some items")

        Button {
            text: qsTr("Perform action")
            onClicked: {
                var l = view.selectedIndexes.length;
                var message = l > 0 ? qsTr("You selected items") + " " : qsTr("You did not select any items");
                var rows = [];
                
                for (var i = 0; i < l; i++) {
                    rows.push(QModelIndex.row(view.selectedIndexes[i]));
                }
                
                message += rows.join(", ");
                
                infobox.showMessage(message);
                pageStack.pop();
            }
        }
    }

    ListView {
        id: view

        anchors {
            left: parent.left
            right: parent.right
            top: editBar.bottom
            bottom: parent.bottom
        }
        model: qsTr("You can select multiple items from this list and perform an action on them").split(" ")
        selectionMode: ListView.MultiSelection
        contextMenuPolicy: Qt.ActionsContextMenu
        actions:[
            Action {
                text: qsTr("Select all")
                onTriggered: view.selectAll()
            },

            Action {
                text: qsTr("Clear selection")
                onTriggered: view.clearSelection()
            }
        ]
    }
}
