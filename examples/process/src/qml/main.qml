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
import org.hildon.utils 1.0

Window {
    id: mainWindow

    windowTitle: qsTr("Process")
    tools: Action {
        text: qsTr("About")
        onTriggered: dialog.open()
    }

    Process {
        id: process

        onFinished: {
            switch (exitStatus) {
            case Process.NormalExit:
                resultEdit.text = standardOutput;
                return;
            default:
                resultEdit.text = standardError;
                return;
            }
        }
    }

    Column {
        id: column

        anchors {
            fill: parent
            margins: 10
        }
        spacing: 10

        Row {

            Label {
                text: qsTr("Command") + ":"
            }

            TextField {
                id: commandEdit

                onTextChanged: process.command = text
            }
        }

        ValueButton {
            id: dirSelector

            text: qsTr("Working directory")
            valueText: qsTr("None chosen")
            onClicked: fileDialog.getExistingDirectory()
        }

        Button {
            text: qsTr("Start")
            onClicked: process.start()
        }

        TextEdit {
            id: resultEdit

            readOnly: true
        }
    }

    FileDialog {
        id: fileDialog

        onAccepted: {
            dirSelector.valueText = selectedFiles[0];
            process.workingDirectory = selectedFiles[0];
        }
    }

    Dialog {
        id: dialog

        windowTitle: qsTr("About")
        content: Label {
            anchors.fill: parent
            wordWrap: true
            text: qsTr("Qt Components Hildon Process is a demo of the Qt Components Hildon Process component.")
        }

        buttons: Button {
            text: qsTr("Done")
            onClicked: dialog.accept()
        }
    }
}
