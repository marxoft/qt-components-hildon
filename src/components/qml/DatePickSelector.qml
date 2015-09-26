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

/*!
    \class DatePickSelector
    \brief A pick selector for choosing a date value.
    
    \ingroup components
    
    \snippet selectors.qml DatePickSelector
    
    \sa ListPickSelector, TimePickSelector, ValueButton
*/  
AbstractPickSelector {
    id: root
    
    /*!
        \brief The minimum year that can be chosen.
        
        The default value is \c 2009
    */
    property int minimumYear: 2009
    
    /*!
        \brief The maximum year that can be chosen.
        
        The default value is \c 2037
    */
    property int maximumYear: 2037
    
    /*!
        \brief The current chosen date.
        
        The default value is the current date.
    */
    property variant currentDate: new Date()
    
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
            id: dayView
                            
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            delegate: defaultDelegate
        }
        
        ListView {
            id: monthView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: [qsTr("January"), qsTr("February"), qsTr("March"), qsTr("April"), qsTr("May"), qsTr("June"),
                    qsTr("July"), qsTr("August"), qsTr("September"), qsTr("October"), qsTr("November"), qsTr("December")]
            delegate: defaultDelegate
            onCurrentIndexChanged: if (internal.ready) internal.updateDays();
        }
        
        ListView {
            id: yearView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            delegate: defaultDelegate
            onCurrentIndexChanged: if (internal.ready) internal.updateDays();
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
            root.currentDate = internal.currentDate();
            root.selected(Qt.formatDate(root.currentDate));
        }
    }
    
    QtObject {
        id: internal
        
        property bool ready: false
                
        function currentDate() {
            return new Date(yearView.model[yearView.currentIndex], monthView.currentIndex + 1,
                            dayView.currentIndex + 1);
        }
        
        function updateCurrentDate() {
            updateDays();
            root.currentValueText = root.currentValueText = Qt.formatDate(root.currentDate);
            dayView.currentIndex = root.currentDate.getDate();
            monthView.currentIndex = root.currentDate.getMonth();
            yearView.currentIndex = root.currentDate.getYear() - yearView.model[0];
        }
        
        function updateDays() {
            var start = 1;
            var end = new Date(yearView.model[yearView.currentIndex], monthView.currentIndex + 1, 0).getDate();
            var days = [];
            
            while (start <= end) {
                days.push(start++);
            }
            
            dayView.model = days;
        }
        
        function updateYears() {
            var start = root.minimumYear;
            var end = root.maximumYear;
            var years = [];
            
            while (start <= end) {
                years.push(start++);
            }
            
            yearView.model = years;
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
        internal.updateYears();
        internal.updateCurrentDate();
        internal.ready = true;
    }
        
    onCurrentDateChanged: if (internal.ready) internal.updateCurrentDate();
    onMinimumYearChanged: if (internal.ready) internal.updateYears();
    onMaximumYearChanged: if (internal.ready) internal.updateYears();
    onSelected: accept()
}
        