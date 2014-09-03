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
        onTriggered: dialog.open()
    }

    ListView {
        id: view
        
        anchors.fill: parent
        model: [ 
            { "name": qsTr("Images"), "icon": "/usr/share/icons/hicolor/48x48/hildon/general_image.png", },
            { "name": qsTr("Audio"), "icon": "/usr/share/icons/hicolor/48x48/hildon/general_audio_file.png", },
            { "name": qsTr("Video"), "icon": "/usr/share/icons/hicolor/48x48/hildon/general_video_file.png", }
        ]
        delegate: MainListDelegate {}
        onClicked: {
            switch (QModelIndex.row(view.currentIndex)) {
            case 0:
                pageStack.push(Qt.resolvedUrl("ImagesPage.qml"), {});
                break;
            case 1:
                pageStack.push(Qt.resolvedUrl("AudioPage.qml"), {});
                break;
            case 2:
                pageStack.push(Qt.resolvedUrl("VideoPage.qml"), {});
                break;
            }
        }
    }

    Dialog {
        id: dialog

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
