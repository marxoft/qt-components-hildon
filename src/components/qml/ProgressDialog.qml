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

    property bool autoClose: true

    property alias minimum: progressBar.minimum
    property alias maximum: progressBar.maximum
    property alias value: progressBar.value

    property alias labelText: label.text

    property alias cancelButtonText: cancelButton.text

    signal cancelled

    function cancel() {
        cancelled();
        close();
    }

    function reset() {
        if (autoClose) {
            close();
        }

        progressBar.value = 0;
    }

    content: Column {
        id: column

        anchors.fill: parent

        Label {
            id: label

            width: column.width
            wordWrap: true
        }

        ProgressBar {
            id: progressBar

            width: column.width
            height: 70
            textVisible: false
            onValueChanged: if (value == maximum) root.close();
        }
    }

    buttons: Button {
        id: cancelButton

        visible: text != ""
        onClicked: root.cancel()
    }
}
