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

    windowTitle: qsTr("Buttons")

    Column {
        anchors {
            fill: parent
            margins: 10
        }
        spacing: 10

        ButtonRow {
            anchors {
                left: parent.left
                right: parent.right
            }
            exclusive: true

            Button {
                checkable: true
                checked: true
                text: qsTr("One")
            }

            Button {
                checkable: true
                text: qsTr("Two")
            }

            Button {
                checkable: true
                text: qsTr("Three")
            }
        }

        Button {
            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Push button")
            onClicked: infobox.showMessage(qsTr("Button clicked"))
        }

        ValueButton {
            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Screen orientation")
            selector: ListSelector {
                model: [ qsTr("Landscape"), qsTr("Portrait"), qsTr("Automatic") ]
                currentIndex: screen.orientationLock === Screen.AutoOrientation ? 2 : screen.orientationLock === Screen.PortraitOrientation ? 1 : 0
                onSelected: {
                    switch (currentIndex) {
                    case 1:
                        screen.orientationLock = Screen.PortraitOrientation;
                        return;
                    case 2:
                        screen.orientationLock = Screen.AutoOrientation;
                        return;
                    default:
                        screen.orientationLock = Screen.LandscapeOrientation;
                        return;
                    }
                }
            }
        }

        ValueButton {
            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Select a date")
            valueText: qsTr("None chosen")
            selector: DateSelector {}
        }

        ValueButton {
            anchors {
                left: parent.left
                right: parent.right
            }
            text: qsTr("Select a time")
            valueText: qsTr("None chosen")
            selector: TimeSelector {}
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
            color: platformStyle.notificationTextColor
        }
    }
}
