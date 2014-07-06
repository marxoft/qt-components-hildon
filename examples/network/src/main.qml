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
import org.hildon.network 1.0

Window {
    id: mainWindow

    windowTitle: qsTr("Network")
    tools: Action {
        text: qsTr("About")
        onTriggered: dialog.open()
    }

    NetworkRequest {
        id: request

        onStatusChanged: {
            switch (status) {
            case NetworkRequest.Ready:
                console.log(responseData);
                return;
            case NetworkRequest.Error:
                console.log(errorString);
                return;
            case NetworkRequest.Loading:
                console.log("Loading " + url.toString())
                return;
            }
        }
    }

    Flickable {
        id: flicker

        anchors {
            fill: parent
            margins: 10
        }

        Column {
            id: column

            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            spacing: 10

            Row {

                Label {
                    text: qsTr("URL") + ":"
                }

                TextField {
                    id: urlEdit
                }
            }

            Row {

                Label {
                    text: qsTr("Headers") + ":"
                }

                TextField {
                    id: headersEdit
                }
            }

            Row {

                Label {
                    text: qsTr("Data") + ":"
                }

                TextField {
                    id: dataEdit
                }
            }

            ValueButton {
                id: fileSelector

                text: qsTr("Local file")
                valueText: qsTr("None chosen")
                onClicked: fileDialog.open()
            }

            ValueButton {
                text: qsTr("Request method")
                selector: ListSelector {
                    id: methodSelector

                    model: [ qsTr("get"), qsTr("getFile"), qsTr("put"), qsTr("putFile"), qsTr("post"), qsTr("postFile") ]
                    currentIndex: 0
                }
            }

            Button {
                text: qsTr("Start")
                onClicked: {
                    request.url = urlEdit.text;
                    request.requestHeaders = headersEdit.text ? eval("(" + headersEdit.text + ")") : {};

                    switch (methodSelector.currentIndex) {
                    case 0:
                        request.get();
                        return;
                    case 1:
                        request.getFile(fileSelector.valueText);
                        return;
                    case 2:
                        request.put(dataEdit.text);
                        return;
                    case 3:
                        request.putFile(fileSelector.valueText);
                        return;
                    case 4:
                        request.post(dataEdit.text);
                        return;
                    case 5:
                        request.postFile(fileSelector.valueText);
                        return;
                    default:
                        return;
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog

        onSelected: fileSelector.valueText = filePath
    }

    Dialog {
        id: dialog

        windowTitle: qsTr("About")
        content: Label {
            anchors.fill: parent
            wordWrap: true
            text: qsTr("Qt Components Hildon Network is a demo of the Qt Components Hildon Network module.")
        }

        buttons: Button {
            text: qsTr("Done")
            onClicked: dialog.accept()
        }
    }
}
