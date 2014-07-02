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
import org.hildon.webkit 1.0

ApplicationWindow {
    id: mainWindow

    windowTitle: qsTr("Browser")
    tools: Action {
        text: qsTr("About")
        onTriggered: dialog.open()
    }

    WebView {
        id: webView

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: toolbar.top
        }
    }

    ToolBar {
        id: toolbar

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Action {
            icon: "general_backspace"
            enabled: webView.status != WebView.Null
            onTriggered: webView.back()
        }

        TextField {
            validator: RegExpValidator {
                regExp: /http(s|):\/\/.+/
            }
            onReturnPressed: if (acceptableInput) webView.url = text
        }

        Action {
            icon: webView.status == WebView.Loading ? "general_stop" : "general_refresh"
            enabled: webView.status != WebView.Null
            onTriggered: webView.status == WebView.Loading ? webView.stop() : webView.reload()
        }
    }

    Dialog {
        id: dialog

        windowTitle: qsTr("About")
        content: Label {
            anchors.fill: parent
            wordWrap: true
            text: qsTr("Qt Components Hildon Browser is a demo of Qt Components Hildon Webkit.")
        }

        buttons: Button {
            text: qsTr("Done")
            onClicked: dialog.accept()
        }
    }
}
