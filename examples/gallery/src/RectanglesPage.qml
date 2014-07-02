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

    windowTitle: qsTr("Rectangles")
    contextMenuPolicy: Qt.ActionsContextMenu
    tools: Action {
        id: propertiesAction

        text: qsTr("Set properties")
        onTriggered: {
            colorEdit.text = rectangle.color;
            opacitySpinbox.value = rectangle.opacity;
            radiusSpinbox.value = rectangle.radius;
            borderColorEdit.text = rectangle.border.color;
            borderWidthSpinbox.value = rectangle.border.width;
            gradientCheckbox.checked = rectangle.gradient != null;
            smoothCheckbox.checked = rectangle.smooth;
            propertiesDialog.open();
        }
    }

    Rectangle {
        id: rectangle

        anchors {
            fill: parent
            margins: 10
        }
        smooth: true
        color: "lightsteelblue"
    }

    Gradient {
        id: gradient

        GradientStop { position: 0.0; color: rectangle.color }
        GradientStop { position: 1.0; color: Qt.darker(rectangle.color) }
    }

    Dialog {
        id: propertiesDialog

        windowTitle: qsTr("Properties")
        height: root.inPortrait ? 600 : 340
        content: Flickable {
            id: flicker

            anchors.fill: parent

            Column {
                width: flicker.width - 10

                Label {
                    text: qsTr("Color")
                }

                TextField {
                    id: colorEdit
                }

                Label {
                    text: qsTr("Opacity")
                }

                DoubleSpinBox {
                    id: opacitySpinbox

                    maximum: 1.0
                    singleStep: 0.1
                }

                Label {
                    text: qsTr("Radius")
                }

                DoubleSpinBox {
                    id: radiusSpinbox

                    maximum: 50
                }

                Label {
                    text: qsTr("Border color")
                }

                TextField {
                    id: borderColorEdit
                }

                Label {
                    text: qsTr("Border width")
                }

                SpinBox {
                    id: borderWidthSpinbox

                    maximum: 20
                }

                CheckBox {
                    id: gradientCheckbox

                    text: qsTr("Apply gradient")
                }

                CheckBox {
                    id: smoothCheckbox

                    text: qsTr("Smooth")
                }
            }
        }

        buttons: Button {
            text: qsTr("Done")
            onClicked: propertiesDialog.accept()
        }

        onAccepted: {
            rectangle.color = colorEdit.text;
            rectangle.opacity = opacitySpinbox.value;
            rectangle.radius = radiusSpinbox.value;
            rectangle.border.color = borderColorEdit.text;
            rectangle.border.width = borderWidthSpinbox.value;
            rectangle.gradient = gradientCheckbox.checked ? gradient : null;
            rectangle.smooth = smoothCheckbox.checked;
        }
    }
}
