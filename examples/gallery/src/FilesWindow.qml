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
    id: root

    windowTitle: qsTr("Files")

    Column {
        anchors {
            fill: parent
            margins: 10
        }
        spacing: 20

        ValueButton {
            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Select a file")
            valueText: fileDialog.selectedFiles.length > 0 ? fileDialog.selectedFiles.join(", ") : qsTr("None chosen")
            onClicked: {
                fileDialog.caption = text;
                fileDialog.getOpenFileName();
            }
        }

        ValueButton {
            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Select a directory")
            valueText: dirDialog.selectedFiles.length > 0 ? dirDialog.selectedFiles.join(", ") : qsTr("None chosen")
            onClicked: {
                dirDialog.caption = text;
                dirDialog.getExistingDirectory();
            }
        }
    }

    FileDialog {
        id: fileDialog

        directory: "/home/user/MyDocs/"
    }

    FileDialog {
        id: dirDialog

        directory: "/home/user/MyDocs/"
    }
}
