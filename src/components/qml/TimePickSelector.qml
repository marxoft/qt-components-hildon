/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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

/*!
    \class TimePickSelector
    \brief A pick selector used for choosing a time value.
    
    \ingroup components
    
    \snippet selectors.qml TimePickSelector
    
    \sa DatePickSelector, TimePickSelector, ValueButton
*/
AbstractPickSelector {
    id: root
        
    /*!
        \brief The current chosen hour.
        
        The default value is the current hour.
    */
    property int hour: dateTime.currentHour()
    
    /*!
        \brief The current chosen minute.
        
        The default value is the current minute.
    */
    property int minute: dateTime.currentMinute()
    
    /*!
        \brief The interval between each minute value displayed.
        
        The default value is \c 1.
    */
    property int minuteStep: 1
    
    /*!
        \brief The format used for the time value text.
        
        The default value is \c "h:mm ap".
    */
    property variant valueTextFormat: "h:mm ap"
    
    height: 360
    
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
            model: ListModel {
                id: hourModel
                
                ListElement { name: 12; value: 0 }
                ListElement { name: 1; value: 1 }
                ListElement { name: 2; value: 2 }
                ListElement { name: 3; value: 3 }
                ListElement { name: 4; value: 4 }
                ListElement { name: 5; value: 5 }
                ListElement { name: 6; value: 6 }
                ListElement { name: 7; value: 7 }
                ListElement { name: 8; value: 8 }
                ListElement { name: 9; value: 9 }
                ListElement { name: 10; value: 10 }
                ListElement { name: 11; value: 11 }
            }
            delegate: defaultDelegate
        }
        
        ListView {
            id: minuteView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: ListModel {
                id: minuteModel
            }
            delegate: defaultDelegate
        }
        
        ListView {
            id: ampmView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: ListModel {
                id: ampmModel
            }
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
            internal.updateValueText();
            root.selected(root.currentValueText);
        }
    }
    
    QtObject {
        id: internal
        
        property bool ready: false
        
        function init() {
            // Script values cannot be used with ListElement
            ampmModel.append({name: dateTime.amText(), value: 0});
            ampmModel.append({name: dateTime.pmText(), value: 12});
            updateMinuteStep();
            updateHour();
            updateMinute();
            updateValueText();
            ready = true;
        }
        
        function reset() {
            updateHour();
            updateMinute();
        }
        
        function updateHour() {
            ampmView.currentIndex = (root.hour > 12 ? 1 : 0);
            hourView.currentIndex = root.hour - ampmModel.get(ampmView.currentIndex).value;
        }
        
        function updateMinute() {
            minuteView.currentIndex = Math.floor(root.minute / root.minuteStep);
        }
        
        function updateMinuteStep() {
            if ((root.minuteStep <= 0) || (root.minuteStep > 60) || (60 % root.minuteStep > 0)) {
                return;
            }
            
            var min = 0;
            var step = root.minuteStep;
            minuteModel.clear();
            
            while (min < 60) {
                minuteModel.append({name: min, value: min});
                min += step;
            }
            
            minuteView.currentIndex = 0;
        }
        
        function updateValueText() {
            root.hour = hourModel.get(hourView.currentIndex).value + ampmModel.get(ampmView.currentIndex).value;
            root.minute = minuteModel.get(minuteView.currentIndex).value;
            root.currentValueText = Qt.formatTime(dateTime.time(root.hour, root.minute), root.valueTextFormat);
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
                    leftMargin: platformStyle.paddingMedium
                    right: parent.right
                    rightMargin: platformStyle.paddingMedium
                    verticalCenter: parent.verticalCenter
                }
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                text: name
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
    
    Component.onCompleted: internal.init()
    
    onHourChanged: if (internal.ready) internal.updateHour();
    onMinuteChanged: if (internal.ready) internal.updateMinute();
    onMinuteStepChanged: if (internal.ready) internal.updateMinuteStep();
    onRejected: if (internal.ready) internal.reset();
    onSelected: accept()
}
        
