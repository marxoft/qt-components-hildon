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
import org.hildon.dbus 1.0

Window {
    id: mainWindow

    windowTitle: qsTr("DBus")
    tools: Action {
        text: qsTr("About")
        onTriggered: dialog.open()
    }

    DBusAdaptor {
        id: adaptor

        serviceName: "org.hildon.QtComponentsHildon"
        path: "/org/hildon/QtComponentsHildon"
        target: mainWindow
    }

    DBusMessage {
        id: message
       
        bus: busSelector.currentIndex
        type: typeSelector.currentIndex
        serviceName: serviceField.text
        path: pathField.text
        interfaceName: interfaceField.text
        methodName: methodField.text
        onStatusChanged: {
            switch (status) {
            case DBusMessage.Loading:
                replyField.text = qsTr("Loading");
                return;
            case DBusMessage.Ready:
            {
                replyField.text = replyString;
                infobox.showMessage(qsTr("Message sent successfully"));
                return;
            }
            case DBusMessage.Error:
            {
                replyField.text = qsTr("Error");
                infobox.showMessage(qsTr("Error sending message"));
                return;
            }
            default:
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

            ValueButton {
                text: qsTr("Bus type")
                valueText: qsTr("Session bus")
                selector: ListSelector {
                    id: busSelector

                    model: [ qsTr("Session bus"), qsTr("System bus") ]
                }
            }

            ValueButton {
                text: qsTr("Message type")
                valueText: qsTr("Method call")
                selector: ListSelector {
                    id: typeSelector

                    model: [ qsTr("Method call"), qsTr("Signal") ]
                }
            }

            Label {
                text: qsTr("Service")
            }

            TextField {
                id: serviceField
            }

            Label {
                text: qsTr("Path")
            }

            TextField {
                id: pathField
            }

            Label {
                text: qsTr("Interface")
            }

            TextField {
                id: interfaceField
            }

            Label {
                text: qsTr("Method/signal name")
            }

            TextField {
                id: methodField
            }

            Label {
                text: qsTr("Arguments")
            }

            TextField {
                id: argsField
            }

            Button {
                id: sendButton
                
                text: qsTr("Send")
                onClicked: {
                    message.arguments = (argsField.text ? eval("(" + argsField.text + ")") : []);
                    message.send();
                }
            }

            Label {
                text: qsTr("Reply")
            }

            TextEdit {
                id: replyField

                height: 200
                readOnly: true
            }
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

    Dialog {
        id: dialog

        windowTitle: qsTr("About")
        content: Label {
            anchors.fill: parent
            wordWrap: true
            text: qsTr("Qt Components Hildon DBus is a demo of the Qt Components Hildon DBus module.")
        }

        buttons: Button {
            id: dialogButton
            text: qsTr("Done")
            onClicked: dialog.accept()
        }
    }
}
