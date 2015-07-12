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
import "."

AbstractPickSelector {
    id: root
    
    property int minuteStep: 1
    property variant currentTime: new Date()
    
    minimumHeight: 350
    
    Row {
        id: row
        
        anchors {
            left: parent.left
            right: button.left
            rightMargin: platformStyle.paddingMedium
            top: parent.top
            bottom: parent.bottom
        }
        
        ListView {
            id: hourView
                            
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            delegate: defaultDelegate
            model: [12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
        }
        
        ListView {
            id: minView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            delegate: defaultDelegate
        }
        
        ListView {
            id: ampmView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: [qsTr("am"), qsTr("pm")]
            delegate: defaultDelegate
        }
    }
    
    Button {
        id: button
        
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        focus: true
        text: qsTr("Done")
        style: DialogButtonStyle {}
        enabled: internal.ready
        onClicked: {
            root.currentTime = internal.currentTime();
            root.selected(Qt.formatTime(root.currentTime));
        }
    }
    
    QtObject {
        id: internal
        
        property bool ready: false
        
        function currentTime() {
            var time = new Date();
            time.setHours(hourView.currentIndex + ampmView.currentIndex * 12);
            time.setMinutes(minView.currentIndex);
            return time;
        }
        
        function updateCurrentTime() {
            root.currentValueText = Qt.formatTime(root.currentTime);
            var hours = root.currentTime.getHours();
            var mins = root.currentTime.getMinutes();
            
            ampmView.currentIndex = hours > 11 ? 1 : 0
            hourView.currentIndex = hours - ampmView.currentIndex * 12;
            minView.currentIndex = Math.floor(mins / Math.max(1, root.minuteStep));
        }
        
        function updateMinuteStep() {
            var mins = [];
            var min = 0;
            var step = Math.max(1, root.minuteStep);
            
            while (min < 60) {
                mins.push(min);
                min += step;
            }
            
            minView.model = mins;
            minView.currentIndex = Math.floor(root.currentTime.getMinutes() / step);
        }
    }
    
    Component {
        id: defaultDelegate
        
        ListItem {
            id: item
            
            style: ListItemStyle {
                background: "image://theme/TouchListBackground" + (item.ListView.isCurrentItem ? "Pressed" : "Normal")
            }
                                    
            Label {
                id: label
                
                anchors {
                    left: parent.left
                    leftMargin: item.style.paddingLeft
                    right: parent.right
                    rightMargin: item.style.paddingRight
                    verticalCenter: parent.verticalCenter
                }
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                text: modelData
            }            
        }
    }
    
    StateGroup {
        states: State {
            name: "Portrait"
            when: screen.currentOrientation == Qt.WA_Maemo5PortraitOrientation
            
            AnchorChanges {
                target: row
                anchors {
                    right: parent.right
                    bottom: button.top
                }
            }
            
            PropertyChanges {
                target: row
                anchors {
                    rightMargin: 0
                    bottomMargin: platformStyle.paddingMedium
                }
            }
            
            PropertyChanges {
                target: button
                width: parent.width
            }
        }
    }
    
    Component.onCompleted: {
        internal.updateMinuteStep();
        internal.updateCurrentTime();
        internal.ready = true;
    }
    
    onCurrentTimeChanged: if (internal.ready) internal.updateCurrentTime();
    onMinuteStepChanged: if (internal.ready) internal.updateMinuteStep();
    onSelected: accept()
}
        