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

    windowTitle: qsTr("ScreenShot")
    tools: [
        Action {
            text: qsTr("Take screenshot")
            onTriggered: timer.restart()
        },

        Action {
            text: qsTr("Settings")
            onTriggered: {
                fileNameEdit.text = screenshot.fileName;
                overwriteCheckbox.checked = screenshot.overwriteExistingFile;
                widthSpinbox.value = screenshot.width;
                heightSpinbox.value = screenshot.height;
                targetXSpinbox.value = screenshot.targetX;
                targetYSpinbox.value = screenshot.targetY;
                targetWidthSpinbox.value = screenshot.targetWidth;
                targetHeightSpinbox.value = screenshot.targetHeight;
                smoothCheckbox.checked = screenshot.smooth;
                settingsDialog.open();
            }
        },

        Action {
            text: qsTr("About")
            onTriggered: dialog.open()
        }
    ]

    Image {
        id: image

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }

        height: Math.floor(width * 0.6)
        fillMode: Image.PreserveAspectFit
    }

    ScreenShot {
        id: screenshot

        fileName: "/home/user/MyDocs/screenshot.png"
    }

    Timer {
        id: timer

        interval: 0
        onTriggered: {
            if (screenshot.grab()) {
                infobox.showMessage(qsTr("Screenshot saved to") + " " + screenshot.fileName);
                image.source = "file://" + screenshot.fileName
            }
            else {
                infobox.showMessage(qsTr("Cannot save screenshot to") + " " + screenshot.fileName);
                image.source = "";
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
        id: settingsDialog

        windowTitle: qsTr("Settings")
        height: mainWindow.inPortrait ? 600 : 340
        content: Flickable {
            id: flicker

            anchors.fill: parent

            Column {
                width: flicker.width - 10

                Label {
                    text: qsTr("Timeout (msecs)")
                }

                SpinBox {
                    id: timeoutSpinbox

                    maximum: 30000
                    singleStep: 1000
                }

                Label {
                    text: qsTr("Filename")
                }

                TextField {
                    id: fileNameEdit
                }

                CheckBox {
                    id: overwriteCheckbox

                    text: qsTr("Overwrite existing file")
                }

                Label {
                    text: qsTr("Width")
                }

                SpinBox {
                    id: widthSpinbox

                    minimum: -1
                    maximum: 800
                }

                Label {
                    text: qsTr("Height")
                }

                SpinBox {
                    id: heightSpinbox

                    minimum: -1
                    maximum: 480
                }

                Label {
                    text: qsTr("Target X")
                }

                SpinBox {
                    id: targetXSpinbox

                    minimum: -1
                    maximum: 800
                }

                Label {
                    text: qsTr("Target Y")
                }

                SpinBox {
                    id: targetYSpinbox

                    minimum: -1
                    maximum: 480
                }

                Label {
                    text: qsTr("Target width")
                }

                SpinBox {
                    id: targetWidthSpinbox

                    minimum: -1
                    maximum: 800
                }

                Label {
                    text: qsTr("Target height")
                }

                SpinBox {
                    id: targetHeightSpinbox

                    minimum: -1
                    maximum: 480
                }

                CheckBox {
                    id: smoothCheckbox

                    text: qsTr("Smooth scaling")
                }
            }
        }

        buttons: Button {
            text: qsTr("Save")
            enabled: fileNameEdit.text != ""
            onClicked: settingsDialog.accept()
        }

        onAccepted: {
            timer.interval = timeoutSpinbox.value;
            screenshot.fileName = fileNameEdit.text;
            screenshot.overwriteExistingFile = overwriteCheckbox.checked
            screenshot.width = widthSpinbox.value;
            screenshot.height = heightSpinbox.value;
            screenshot.targetX = targetXSpinbox.value;
            screenshot.targetY = targetYSpinbox.value;
            screenshot.targetWidth = targetWidthSpinbox.value;
            screenshot.targetHeight = targetHeightSpinbox.value;
            screenshot.smooth = smoothCheckbox.checked;
        }
    }

    Dialog {
        id: dialog

        windowTitle: qsTr("About")
        content: Label {
            anchors.fill: parent
            wordWrap: true
            text: qsTr("Qt Components Hildon ScreenShot is a demo of the Qt Components Hildon Utils module.")
        }

        buttons: Button {
            text: qsTr("Done")
            onClicked: dialog.accept()
        }
    }
}
