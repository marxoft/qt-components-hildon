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

/*!
    \class CheckBox
    \brief A checkable button with a visible indicator.
    
    \ingroup components
    
    \include checkbox.qml
    
    \sa CheckBoxStyle, OssoCheckBoxStyle
*/
AbstractButton {
    id: root
    
    /*!
        type:CheckBoxStyle
        \brief Provides styling properties for the checkbox.
    */
    property QtObject style: CheckBoxStyle {}
    
    checkable: true
    width: style.buttonWidth
    height: style.buttonHeight
    
    BorderImage {
        id: background
        
        anchors.fill: parent
        border {
            left: root.style.backgroundMarginLeft
            right: root.style.backgroundMarginRight
            top: root.style.backgroundMarginTop
            bottom: root.style.backgroundMarginBottom
        }
        smooth: true
        source: root.pressed ? root.style.backgroundPressed : root.checked ? root.style.backgroundChecked
                : !root.enabled ? root.style.backgroundDisabled : root.style.background
    }
    
    Row {
        id: row
        
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            bottom: parent.bottom
            leftMargin: root.style.paddingLeft
            rightMargin: root.style.paddingRight
        }
        spacing: platformStyle.paddingMedium

        Image {
            id: icon
            
            y: Math.floor((root.height - height) / 2)
            width: Math.min(root.style.iconWidth, sourceSize.width)
            height: Math.min(root.style.iconHeight, sourceSize.height)
            smooth: true
            source: root.style.icon
            visible: source != ""
        }
        
        Label {
            id: label
            
            height: parent.height
            font {
                pointSize: Math.max(1, root.style.fontPointSize)
                capitalization: root.style.fontCapitalization
                weight: root.style.fontWeight
            }
            color: root.pressed ? root.style.pressedTextColor : root.checked ? root.style.checkedTextColor
                   : !root.enabled ? root.style.disabledTextColor : root.style.textColor
            verticalAlignment: Text.AlignVCenter
            text: textMetrics.elidedText
            visible: text != ""
            
            TextMetrics {
                id: textMetrics
                
                font: label.font
                elide: Qt.ElideRight
                elideWidth: root.width - root.style.paddingLeft - root.style.paddingRight
                            - (icon.visible ? icon.width + platformStyle.paddingMedium : 0)
                text: root.text
            }
        }
    }
    
    StateGroup {
        id: alignmentStates
        
        states: [
            State {
                name: "AlignLeft"
                when: root.style.horizontalAlignment == Qt.AlignLeft
                
                AnchorChanges {
                    target: row
                    anchors {
                        left: parent.left
                        horizontalCenter: undefined
                    }
                }
            },
            
            State {
                name: "AlignRight"
                when: root.style.horizontalAlignment == Qt.AlignRight
                
                AnchorChanges {
                    target: row
                    anchors {
                        right: parent.right
                        horizontalCenter: undefined
                    }
                }
            }
        ]
    }
    
    StateGroup {
        id: iconStates
        
        states: [
            State {
                name: "Checked"
                when: root.checked
                
                PropertyChanges {
                    target: icon
                    source: root.style.iconChecked
                }
            },
            
            State {
                name: "CheckedDisabled"
                when: (root.checked) && (!root.enabled)
                
                PropertyChanges {
                    target: icon
                    source: root.style.iconCheckedDisabled
                }
            },
            
            State {
                name: "CheckedPressed"
                when: (root.checked) && (root.pressed)
                
                PropertyChanges {
                    target: icon
                    source: root.style.iconCheckedPressed
                }
            },
            
            State {
                name: "Disabled"
                when: !root.enabled
                
                PropertyChanges {
                    target: icon
                    source: root.style.iconDisabled
                }
            },
                        
            State {
                name: "Pressed"
                when: root.pressed
                
                PropertyChanges {
                    target: icon
                    source: root.style.iconPressed
                }
            }
        ]
    }
}
