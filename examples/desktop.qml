/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.desktop 1.0

Window {
    id: window
        
    title: qsTr("Desktop example")
    visible: true
        
    Column {        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
        Button {
            width: parent.width
            text: qsTr("Show widget")
            onClicked: widgetComponent.createObject(null)
        }
        
        Button {
            id: notificationButton
            
            width: parent.width
            text: qsTr("Show notification")
            onClicked: notificationComponent.createObject(window)
        }
    }
    
    Component {
        id: widgetComponent
        
        HomescreenWidget {
            id: widget
            
            property Dialog settingsDialog
            
            width: Math.max(100, widgetLabel.width * 2)
            height: widgetLabel.height * 2
            settingsAvailable: true
            
            Rectangle {
                id: widgetBackground
                
                anchors {
                    fill: parent
                    margins: 1
                }
                color: "#000"
                radius: 25
                opacity: 0.5
                smooth: true
            }
            
            Label {
                id: widgetLabel
                
                anchors.centerIn: parent
                text: qsTr("Hello World")
            }
            
            Component {
                id: dialogComponent
                
                Dialog {
                    id: dialog
                    
                    title: qsTr("New text")
                    height: column.height + platformStyle.paddingMedium
                    
                    Column {
                        id: column
                        
                        anchors {
                            left: parent.left
                            right: button.left
                            rightMargin: platformStyle.paddingMedium
                            bottom: parent.bottom
                        }
                        spacing: platformStyle.paddingMedium
                        
                        Label {
                            width: parent.width
                            text: qsTr("Please enter a new text:")
                        }
                        
                        TextField {
                            id: textField
                            
                            width: parent.width
                        }
                    }
                    
                    Button {
                        id: button
                        
                        anchors {
                            right: parent.right
                            bottom: parent.bottom
                        }
                        style: DialogButtonStyle {}
                        text: qsTr("Done")
                        enabled: textField.text != ""
                        onClicked: dialog.accept()
                    }
                    
                    onAccepted: widgetLabel.text = textField.text
                    onStatusChanged: {
                        if (status == DialogStatus.Open) {
                            textField.text = widgetLabel.text;
                            textField.forceActiveFocus();
                        }
                    }
                }
            }
            
            onSettingsRequested: {
                if (!settingsDialog) {
                    settingsDialog = dialogComponent.createObject(widget);
                }
                
                settingsDialog.open();
            }
        }
    }
    
    Component {
        id: notificationComponent
        
        Notification {
            id: notification
                
            category: "qt-components-hildon"
            hints: {"led-pattern": "PatternCommonNotification"}
            iconSource: "general_web"
            text: qsTr("This is an example QML notification")
            timeout: Notification.DefaultTimeout
            title: qsTr("QML notification")
            visible: true
            onAccepted: console.log(qsTr("Notification accepted"))
            onRejected: console.log(qsTr("Notification rejected"))
        }
    }
}
