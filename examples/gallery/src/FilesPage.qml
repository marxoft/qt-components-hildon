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

    windowTitle: qsTr("Files")

    Column {
        anchors {
            fill: parent
            margins: 10
        }
        spacing: 20

        ValueButton {
            id: fileSelector

            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Select a file")
            valueText: qsTr("None chosen")
            onClicked: fileDialog.open()
        }

        ValueButton {
            id: folderSelector

            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Select a directory")
            valueText: qsTr("None chosen")
            onClicked: folderDialog.open()
        }
    }

    FileDialog {
        id: fileDialog

        showHidden: true
        onSelected: fileSelector.valueText = filePath
    }

    FolderDialog {
        id: folderDialog

        showHidden: true
        onSelected: folderSelector.valueText = folder
    }
}
