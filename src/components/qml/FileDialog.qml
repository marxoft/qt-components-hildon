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
        view.rootIndex = proxyModel.mapFromSource(fileModel.index(path));
    }

    function cdUp() {
        view.rootIndex = proxyModel.mapFromSource(fileModel.index(fileModel.filePath(proxyModel.mapToSource(view.rootIndex)).substring(0, fileModel.filePath(proxyModel.mapToSource(view.rootIndex)).lastIndexOf("/"))));
    }

    height: screen.currentOrientation === Screen.PortraitOrientation ? 680 : 360
    windowTitle: qsTr("Open file")
    content: Column {
        anchors.fill: parent

        Row {
            Button {
                width: 80
                icon: "filemanager_folder_up"
                enabled: fileModel.filePath(proxyModel.mapToSource(view.rootIndex)) !== "/"
                onClicked: root.cdUp()
            }

            Label {
                width: parent.width - 90
                text: fileModel.filePath(proxyModel.mapToSource(view.rootIndex))
            }
        }

        ListView {
            id: view

            model: SortFilterProxyModel {
                id: proxyModel
                
                sourceModel: FileSystemModel {
                    id: fileModel

                    rootPath: "/"
                    showFiles: true
                    showDotAndDotDot: false
                    nameFilterDisables: false
                    readOnly: true
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
    
    Keys.onPressed: if ((!filterEdit.focus) && (!/^\s/.test(event.text))) filterEdit.text += event.text;

    onAccepted: selected(fileModel.filePath(proxyModel.mapToSource(view.currentIndex)))
    onVisibleChanged: if (!visible) toolBar.visible = false;
}
