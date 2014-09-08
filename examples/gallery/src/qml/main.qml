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

Window {
    id: mainWindow

    windowTitle: qsTr("Gallery")
    tools: [
        Action {
            text: qsTr("Change orientation")
            onTriggered: screen.orientationLock = (screen.orientationLock === Screen.LandscapeOrientation ? Screen.PortraitOrientation : Screen.LandscapeOrientation)
        },

        Action {
            text: qsTr("About")
            onTriggered: {
                loader.sourceComponent = dialog;
                loader.item.open();
            }
        }
    ]

    Grid {
        anchors {
            fill: parent
            margins: platformStyle.paddingMedium
        }
        columns: mainWindow.inPortrait ? 1 : 2

        Button {
            text: qsTr("Buttons")
            onClicked: pageStack.push(Qt.resolvedUrl("ButtonsPage.qml"), {})
        }

        Button {
            text: qsTr("Text input")
            onClicked: pageStack.push(Qt.resolvedUrl("TextInputPage.qml"), {})
        }

        Button {
            text: qsTr("Files")
            onClicked: pageStack.push(Qt.resolvedUrl("FilesPage.qml"), {})
        }

        Button {
            text: qsTr("Groups")
            onClicked: pageStack.push(Qt.resolvedUrl("GroupsPage.qml"), {})
        }

        Button {
            text: qsTr("ListView")
            onClicked: pageStack.push(Qt.resolvedUrl("ListViewPage.qml"), {})
        }

        Button {
            text: qsTr("TableView")
            onClicked: pageStack.push(Qt.resolvedUrl("TableViewPage.qml"), {})
        }

        Button {
            text: qsTr("Repeater")
            onClicked: pageStack.push(Qt.resolvedUrl("RepeaterPage.qml"), {})
        }

        Button {
            text: qsTr("MouseArea")
            onClicked: pageStack.push(Qt.resolvedUrl("MouseAreaPage.qml"), {})
        }

        Button {
            text: qsTr("Images")
            onClicked: pageStack.push(Qt.resolvedUrl("ImagesPage.qml"), {})
        }

        Button {
            text: qsTr("Rectangles")
            onClicked: pageStack.push(Qt.resolvedUrl("RectanglesPage.qml"), {})
        }
    }

    InformationBox {
        id: infobox

        function showMessage(message) {
            label.text = message;
            open();
        }

        content: Label {
            id: label

            anchors.fill: parent
            alignment: Qt.AlignCenter
            color: platformStyle.reversedTextColor
        }
    }

    Loader {
        id: loader
    }
    
    Component {
        id: dialog
        
        Dialog {
            windowTitle: qsTr("About")
            content: Label {
                anchors.fill: parent
                wordWrap: true
                text: qsTr("Qt Components Hildon Gallery is a demo of Qt Components Hildon.")
            }

            buttons: Button {
                text: qsTr("Done")
                onClicked: dialog.accept()
            }
        }
    }
}
