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

    windowTitle: qsTr("Images")
    tools: [
        ActionGroup {
            exclusive: true

            Action {
                checkable: true
                checked: true
                text: qsTr("Image")
                onTriggered: tabGroup.currentTab = imageTab
            }

            Action {
                checkable: true
                text: qsTr("BorderImage")
                onTriggered: tabGroup.currentTab = borderImageTab
            }
        },

        Action {
            text: qsTr("Clear images")
            onTriggered: {
                image.source = "";
                borderImage.source = "";
                imageSourceEdit.text = "";
                borderImageSourceEdit.text = "";
            }
        }
    ]

    TabGroup {
        id: tabGroup

        anchors.fill: parent

        Item {
            id: imageTab

            Column {
                id: imageColumn

                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    margins: 10
                }

                TextField {
                    id: imageSourceEdit

                    placeholderText: qsTr("Image source")
                }

                ValueButton {
                    text: qsTr("Fill mode")
                    valueText: "Stretch"
                    selector: ListSelector {
                        id: fillModeSelector

                        model: [ "Stretch", "PreserveAspectFit", "PreserveAspectCrop", "Tile", "TileHorizontally", "TileVertically" ]
                        currentIndex: 0
                    }
                }

                Button {
                    text: qsTr("Load image")
                    enabled: (imageSourceEdit.text != "") && (image.status != Image.Loading)
                    onClicked: {
                        image.source = "";
                        image.fillMode = fillModeSelector.currentValueText;
                        image.source = imageSourceEdit.text;
                    }
                }
            }

            Image {
                id: image

                anchors {
                    fill: parent
                    topMargin: imageColumn.height + 20
                }
                smooth: true

                Label {
                    anchors.fill: parent
                    alignment: Qt.AlignCenter
                    color: "red"
                    text: qsTr("Error loading image")
                    visible: image.status == Image.Error
                }
            }
        }

        Item {
            id: borderImageTab

            Column {
                id: borderImageColumn

                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    margins: 10
                }

                TextField {
                    id: borderImageSourceEdit

                    placeholderText: qsTr("Image source")
                }

                ValueButton {
                    text: qsTr("Tile mode")
                    valueText: "Stretch"
                    selector: ListSelector {
                        id: tileModeSelector

                        model: [ "Stretch", "Repeat", "Round" ]
                        currentIndex: 0
                    }
                }

                Button {
                    text: qsTr("Load image")
                    enabled: (borderImageSourceEdit.text != "") && (borderImage.status != BorderImage.Loading)
                    onClicked: {
                        borderImage.source = "";
                        borderImage.horizontalTileMode = tileModeSelector.currentValueText;
                        borderImage.verticalTileMode = tileModeSelector.currentValueText;
                        borderImage.source = borderImageSourceEdit.text;
                    }
                }
            }

            BorderImage {
                id: borderImage

                anchors {
                    fill: parent
                    topMargin: borderImageColumn.height + 20
                }
                smooth: true

                Label {
                    anchors.fill: parent
                    alignment: Qt.AlignCenter
                    color: "red"
                    text: qsTr("Error loading image")
                    visible: borderImage.status == Image.Error
                }
            }
        }
    }


}
