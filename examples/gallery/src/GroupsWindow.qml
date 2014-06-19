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

    windowTitle: qsTr("Groups")
    tools: ActionGroup {
        exclusive: true

        Action {
            checkable: true
            checked: true
            text: qsTr("One")
            onTriggered: tabGroup.currentIndex = 0
        }

        Action {
            checkable: true
            text: qsTr("Two")
            onTriggered: tabGroup.currentIndex = 1
        }

        Action {
            checkable: true
            text: qsTr("Three")
            onTriggered: tabGroup.currentIndex = 2
        }
    }

    TabGroup {
        id: tabGroup

        anchors.fill: parent

        Label {
            alignment: Qt.AlignCenter
            font.bold: true
            font.pixelSize: 40
            color: platformStyle.activeTextColor
            wordWrap: true
            text: qsTr("Showing tab one")
        }

        Label {
            alignment: Qt.AlignCenter
            font.bold: true
            font.pixelSize: 40
            color: platformStyle.activeTextColor
            wordWrap: true
            text: qsTr("Showing tab two")
        }

        Label {
            alignment: Qt.AlignCenter
            font.bold: true
            font.pixelSize: 40
            color: platformStyle.activeTextColor
            wordWrap: true
            text: qsTr("Showing tab three")
        }
    }
}
