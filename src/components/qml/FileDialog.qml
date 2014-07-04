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
    property alias showDirs: fileModel.showDirs
    property alias showHidden: fileModel.showHidden
    property alias showSymlinks: fileModel.showSymlinks
    property alias resolveSymlinks: fileModel.resolveSymlinks
    property alias nameFilterDisables: fileModel.nameFilterDisables
    property alias nameFilters: fileModel.nameFilters

    signal selected(string filePath)

    function cd(path) {
        view.rootIndex = fileModel.index(path);
    }

    function cdUp() {
        view.rootIndex = fileModel.index(fileModel.filePath(view.rootIndex).substring(0, fileModel.filePath(view.rootIndex).lastIndexOf("/")));
    }

    height: screen.currentOrientation === Screen.PortraitOrientation ? 600 : 340
    windowTitle: qsTr("Open file")
    content: Column {
        anchors.fill: parent

        Row {
            Button {
                width: 80
                icon: "filemanager_folder_up"
                enabled: fileModel.filePath(view.rootIndex) !== "/"
                onClicked: root.cdUp()
            }

            Label {
                width: parent.width - 90
                text: fileModel.filePath(view.rootIndex)
            }
        }

        ListView {
            id: view

            model: FileSystemModel {
                id: fileModel

                rootPath: "/"
                showFiles: true
                showDotAndDotDot: false
                nameFilterDisables: false
                readOnly: true
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

    onAccepted: selected(fileModel.filePath(view.rootIndex))
}
