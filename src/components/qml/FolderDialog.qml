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
import org.hildon.filesystemmodel 1.0

Dialog {
    id: root

    property alias rootPath: fileModel.rootPath
    property alias showHidden: fileModel.showHidden
    property alias showSymlinks: fileModel.showSymlinks
    property alias resolveSymlinks: fileModel.resolveSymlinks
    property alias readOnly: fileModel.readOnly
    property alias nameFilterDisables: fileModel.nameFilterDisables
    property alias nameFilters: fileModel.nameFilters

    signal selected(string folder)

    function cd(path) {
        view.rootIndex = fileModel.index(path);
    }

    function cdUp() {
        view.rootIndex = fileModel.index(fileModel.filePath(view.rootIndex).substring(0, fileModel.filePath(view.rootIndex).lastIndexOf("/")));
    }

    height: screen.currentOrientation === Screen.PortraitOrientation ? 600 : 340
    windowTitle: qsTr("Choose folder")
    content: Column {
        anchors.fill: parent

        Row {

            Button {
                width: 80
                icon: "filemanager_folder_up"
                enabled: fileModel.filePath(view.rootIndex) !== "/"
                onClicked: root.cdUp()
            }

            ValueButton {
                width: parent.width - 90
                icon: !fileModel.fileIcon(view.rootIndex) ? "general_folder" : fileModel.fileIcon(view.rootIndex)
                iconSize: "24x24"
                text: fileModel.fileName(view.rootIndex)
                valueText: fileModel.filePath(view.rootIndex).substring(0, fileModel.filePath(view.rootIndex).lastIndexOf("/"))
                onClicked: root.accept();
            }
        }

        ListView {
            id: view

            model: FileSystemModel {
                id: fileModel

                rootPath: "/"
                showFiles: false
                showDotAndDotDot: false
                nameFilterDisables: false
                readOnly: false
            }
            iconSize: "48x48"
            rootIndex: fileModel.index("/home/user/MyDocs/")
            onClicked: {
                if (fileModel.isDir(currentIndex)) {
                    rootIndex = currentIndex;
                }
                else {
                    root.accept();
                }
            }
        }
    }

    buttons: Button {
        text: qsTr("New")
        enabled: !fileModel.readOnly
        onClicked: newFolderDialog.open()
    }

    Dialog {
        id: newFolderDialog

        height: screen.currentOrientation === Screen.PortraitOrientation ? 220 : 140
        windowTitle: qsTr("New folder")
        content: Column {
            anchors.fill: parent

            TextField {
                id: folderEdit
            }

            Row {

                Image {
                    width: 48
                    height: 48
                    source: "file:///usr/share/icons/hicolor/48x48/hildon/general_folder.png"
                }

                Label {
                    height: 48
                    alignment: Qt.AlignVCenter
                    text: fileModel.fileName(view.rootIndex)
                }
            }
        }

        buttons: Button {
            text: qsTr("Save")
            enabled: folderEdit.text != ""
            onClicked: newFolderDialog.accept()
        }

        onAccepted: {
            view.positionViewAtIndex(fileModel.mkdir(view.rootIndex, folderEdit.text), ListView.EnsureVisible);
            folderEdit.clear();
        }

        onRejected: folderEdit.clear()
    }

    onAccepted: selected(fileModel.filePath(view.rootIndex))
}
