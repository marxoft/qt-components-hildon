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
    id: window

    windowTitle: qsTr("Tracker")
    tools: Action {
        text: qsTr("About")
        onTriggered: {
            loader.sourceComponent = dialog;
            loader.item.open();
        }
    }

    ListView {
        id: view
        
        anchors.fill: parent
        model: [
            {
                "name": qsTr("Images"),
                "icon": "/usr/share/icons/hicolor/48x48/hildon/general_image.png",
                "page": Qt.resolvedUrl("ImagesPage.qml")
            },
            {
                "name": qsTr("Music"),
                "icon": "/usr/share/icons/hicolor/48x48/hildon/general_audio_file.png",
                "page": Qt.resolvedUrl("AudioPage.qml")
            },
            {
                "name": qsTr("Videos"),
                "icon": "/usr/share/icons/hicolor/48x48/hildon/general_video_file.png",
                "page": Qt.resolvedUrl("VideoPage.qml")
            }
        ]
        delegate: MainListDelegate {}
        onActivated: pageStack.push(model[QModelIndex.row(view.currentIndex)].page, {})
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
                text: qsTr("Qt Components Hildon Tracker is a demo of the Qt Components Hildon Tracker module.")
            }

            buttons: Button {
                text: qsTr("Done")
                onClicked: dialog.accept()
            }
        }
    }
}
