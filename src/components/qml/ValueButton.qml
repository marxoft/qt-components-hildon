/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.0
import org.hildon.components 1.0

AbstractButton {
    id: root
    
    property AbstractPickSelector pickSelector
    property ValueButtonStyle style: ValueButtonStyle {}
    property string valueText
    
    width: style.buttonWidth
    height: style.buttonHeight
    
    BorderImage {
        id: background
        
        anchors.fill: parent
        border {
            left: style.backgroundMarginLeft
            right: style.backgroundMarginRight
            top: style.backgroundMarginTop
            bottom: style.backgroundMarginBottom
        }
        smooth: true
        source: root.pressed ? root.style.backgroundPressed : root.checked ? root.style.backgroundChecked
                : !root.enabled ? root.style.backgroundDisabled : root.style.background
    }
    
    Image {
        id: icon
        
        width: Math.min(root.style.iconWidth, sourceSize.width)
        height: Math.min(root.style.iconHeight, sourceSize.height)
        anchors {
            left: parent.left
            leftMargin: root.style.paddingLeft
            verticalCenter: parent.verticalCenter
        }
        smooth: true
        source: root.iconSource ? root.iconSource : iconName ? "image://icon/" + root.iconName : ""
        visible: source != ""
    }
    
    Label {
        id: label
        
        anchors {
            left: icon.visible ? icon.right : parent.left
            leftMargin: root.style.paddingLeft
            right: parent.right
            rightMargin: root.style.paddingRight
            top: parent.top
            topMargin: platformStyle.paddingMedium
        }
        elide: Text.ElideRight
        font {
            pointSize: Math.max(1, root.style.fontPointSize)
            capitalization: root.style.fontCapitalization
            weight: root.style.fontWeight
        }
        color: root.pressed ? root.style.pressedTextColor : root.checked ? root.style.checkedTextColor
               : !root.enabled ? root.style.disabledTextColor : root.style.textColor
        text: root.text
    }
    
    Label {
        id: valueLabel
    
        anchors {
            left: icon.visible ? icon.right : parent.left
            leftMargin: root.style.paddingLeft
            right: parent.right
            rightMargin: root.style.paddingRight
            bottom: parent.bottom
            bottomMargin: platformStyle.paddingMedium
        }
        elide: Text.ElideRight
        font.pointSize: platformStyle.fontSizeSmall
        color: root.pressed ? root.style.pressedTextColor : root.checked ? root.style.checkedTextColor
               : !root.enabled ? root.style.disabledTextColor : root.pickSelector ? root.style.valueTextColor
               : platformStyle.secondaryTextColor
        text: root.valueText
    }
    
    StateGroup {
        states: [
            State {
                name: "ValueBesideText"
                when: root.style.valueLayout == ValueLayout.ValueBesideText
                
                AnchorChanges {
                    target: label
                    anchors {
                        right: parent.horizontalCenter
                        top: undefined
                        verticalCenter: parent.verticalCenter
                    }
                }
                
                AnchorChanges {
                    target: valueLabel
                    anchors {
                        left: parent.horizontalCenter
                        bottom: undefined
                        verticalCenter: parent.verticalCenter
                    }
                }
                
                PropertyChanges {
                    target: valueLabel
                    font.pointSize: platformStyle.fontSizeMedium
                }
            },
            
            State {
                name: "ValueUnderTextCentered"
                when: root.style.valueLayout == ValueLayout.ValueUnderTextCentered
                
                AnchorChanges {
                    target: label
                    anchors.left: parent.left
                }
                
                AnchorChanges {
                    target: valueLabel
                    anchors.left: parent.left
                }
                
                PropertyChanges {
                    target: label
                    horizontalAlignment: Text.AlignHCenter
                }
                
                PropertyChanges {
                    target: valueLabel
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        ]
    }
                
    Connections {
        target: pickSelector
        onCurrentValueTextChanged: valueText = pickSelector.currentValueText
    }
    
    onPickSelectorChanged: {
        if (pickSelector) {
             valueText = pickSelector.currentValueText;
             pickSelector.windowTitle = text;
        }
        else {
            valueText = "";
        }
    }
    onTextChanged: if (pickSelector) pickSelector.windowTitle = text;
    onClicked: if (pickSelector) pickSelector.open();
}
