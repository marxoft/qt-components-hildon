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

Dialog {
    id: root

    property alias rejectButtonText: rejectButton.text
    property alias acceptButtonText: acceptButton.text
    property alias message: label.text

    function open() {
        return exec();
    }

    windowTitle: " "
    modal: true
    content: Label {
        id: label

        anchors {
            fill: parent
            leftMargin: screen.currentOrientation == Screen.PortraitOrientation ? 40 : 100
            rightMargin: leftMargin
        }
        wordWrap: true
    }

    buttons: [
        Button {
            id: acceptButton

            text: qsTr("Yes")
            onClicked: root.accept()
        },

        Button {
            id: rejectButton

            text: qsTr("No")
            onClicked: root.reject()
        }
    ]
}
