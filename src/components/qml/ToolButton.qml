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

AbstractButton {
    id: root
    
    property ToolButtonStyle style: ToolButtonStyle {}
    
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
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        smooth: true
        source: root.iconSource ? root.iconSource : iconName ? "image://icon/" + root.iconName : ""
        opacity: root.enabled ? root.style.iconOpacity : root.style.disabledIconOpacity
        visible: source != ""
    }
    
    Label {
        id: label
        
        anchors {
            left: parent.left
            leftMargin: root.style.paddingLeft
            right: parent.right
            rightMargin: root.style.paddingRight
            verticalCenter: parent.verticalCenter
        }
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        font {
            pointSize: Math.max(1, root.style.fontPointSize)
            capitalization: root.style.fontCapitalization
            weight: root.style.fontWeight
        }
        color: root.pressed ? root.style.pressedTextColor : root.checked ? root.style.checkedTextColor
               : !root.enabled ? root.style.disabledTextColor : root.style.textColor
        text: root.text
        visible: (icon.source == "") || (icon.status == Image.Error)
    }
    
    StateGroup {
        states: [
            State {
                name: "ToolButtonTextOnly"
                when: root.style.toolButtonStyle == Qt.ToolButtonTextOnly
                
                PropertyChanges {
                    target: icon
                    visible: false
                }
                
                PropertyChanges {
                    target: label
                    visible: true
                }
            },
            
            State {
                name: "ToolButtonTextBesideIcon"
                when: root.style.toolButtonStyle == Qt.ToolButtonTextBesideIcon
                
                AnchorChanges {
                    target: icon
                    anchors {
                        horizontalCenter: undefined
                        left: parent.left
                    }
                }
                
                PropertyChanges {
                    target: icon
                    anchors.leftMargin: root.style.paddingLeft
                }
                
                AnchorChanges {
                    target: label
                    anchors.left: icon.right
                }
                
                PropertyChanges {
                    target: label
                    visible: true
                }
            },
            
            State {
                name: "ToolButtonTextUnderIcon"
                when: root.style.toolButtonStyle == Qt.ToolButtonTextUnderIcon
                
                AnchorChanges {
                    target: icon
                    anchors {
                        verticalCenter: undefined
                        top: parent.top
                    }
                }
                
                PropertyChanges {
                    target: icon
                    anchors.topMargin: platformStyle.paddingMedium
                }
                
                AnchorChanges {
                    target: label
                    anchors {
                        verticalCenter: undefined
                        bottom: parent.bottom
                    }
                }
                
                PropertyChanges {
                    target: label
                    anchors.bottomMargin: platformStyle.paddingMedium
                }
            }
        ]
    }
}
