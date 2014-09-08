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

Page {
    id: root

    windowTitle: qsTr("Buttons")

    Flickable {
        id: flicker

        anchors {
            fill: parent
            margins: platformStyle.paddingMedium
        }

        Column {
            id: column

            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }

            ButtonRow {
                width: parent.width
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
                width: parent.width
                text: qsTr("Push button")
                onClicked: infobox.showMessage(qsTr("Button clicked"))
            }

            ValueButton {
                width: parent.width
                text: qsTr("Select values")
                valueText: qsTr("None chosen")
                selector: MultiListSelector {
                    model: 10
                }
            }

            ValueButton {
                width: parent.width
                text: qsTr("Select a date")
                valueText: qsTr("None chosen")
                selector: DateSelector {}
            }

            ValueButton {
                width: parent.width
                text: qsTr("Select a time")
                valueText: qsTr("None chosen")
                selector: TimeSelector {}
            }
        }
    }
}
