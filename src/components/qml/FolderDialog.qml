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
        view.rootIndex = proxyModel.mapFromSource(fileModel.index(path));
    }

    function cdUp() {
        view.rootIndex = proxyModel.mapFromSource(fileModel.index(fileModel.filePath(proxyModel.mapToSource(view.rootIndex)).substring(0, fileModel.filePath(proxyModel.mapToSource(view.rootIndex)).lastIndexOf("/"))));
    }

    height: screen.currentOrientation === Screen.PortraitOrientation ? 680 : 360
    windowTitle: qsTr("Choose folder")
    content: Column {
        anchors.fill: parent

        Row {

            Button {
                width: 80
                icon: "filemanager_folder_up"
                enabled: fileModel.filePath(proxyModel.mapToSource(view.rootIndex)) !== "/"
                onClicked: root.cdUp()
            }

            ValueButton {
                width: parent.width - 90
                icon: !fileModel.fileIcon(proxyModel.mapToSource(view.rootIndex)) ? "general_folder" : fileModel.fileIcon(proxyModel.mapToSource(view.rootIndex))
                iconSize: "24x24"
                text: fileModel.fileName(proxyModel.mapToSource(view.rootIndex))
                valueText: fileModel.filePath(proxyModel.mapToSource(view.rootIndex)).substring(0, fileModel.filePath(proxyModel.mapToSource(view.rootIndex)).lastIndexOf("/"))
                onClicked: root.accept();
            }
        }

        ListView {
            id: view

            model: SortFilterProxyModel {
                id: proxyModel
                
                sourceModel: FileSystemModel {
                    id: fileModel

                    rootPath: "/"
                    showFiles: false
                    showDotAndDotDot: false
                    nameFilterDisables: false
                    readOnly: false
                }
                dynamicSortFilter: true
                filterRegExp: filterEdit.text ? eval("(/" + filterEdit.text + "/i)") : /^/
            }
            horizontalScrollMode: ListView.ScrollPerItem
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            iconSize: "48x48"
            rootIndex: proxyModel.mapFromSource(fileModel.index("/home/user/MyDocs/"))
            onClicked: {
                if (fileModel.isDir(proxyModel.mapToSource(currentIndex))) {
                    rootIndex = currentIndex;
                }
                else {
                    root.accept();
                }
            }
        }
        
        ToolBar {
            id: toolBar
            
            visible: false
            movable: false
            
            TextField {
                id: filterEdit
                
                onTextChanged: if (text) toolBar.visible = true;
            }
            
            Action {
                icon: "general_close"
                onTriggered: toolBar.visible = false
            }
            
            onVisibleChanged: {
                if (visible) {
                    filterEdit.focus = true;
                }
                else {
                    filterEdit.clear();
                }
            }
        }
    }

    buttons: Button {
        text: qsTr("New")
        enabled: !fileModel.readOnly
        onClicked: {
            loader.sourceComponent = newFolderDialog;
            loader.item.open();
        }
    }
    
    Loader {
        id: loader
    }

    Component {
        id: newFolderDialog
        
        Dialog {
            height: screen.currentOrientation === Screen.PortraitOrientation ? 260 : 140
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
                        text: fileModel.fileName(proxyModel.mapToSource(view.rootIndex))
                    }
                }
            }

            buttons: Button {
                text: qsTr("Save")
                enabled: folderEdit.text != ""
                onClicked: newFolderDialog.accept()
            }

            onAccepted: {
                view.positionViewAtIndex(fileModel.mkdir(proxyModel.mapToSource(view.rootIndex), folderEdit.text), ListView.EnsureVisible);
                folderEdit.clear();
            }

            onRejected: folderEdit.clear()
        }
    }
    
    Keys.onPressed: if ((!filterEdit.focus) && (event.text != " ")) filterEdit.text += event.text;

    onAccepted: selected(fileModel.filePath(proxyModel.mapToSource(view.rootIndex)))
    onVisibleChanged: if (!visible) toolBar.visible = false;
}
