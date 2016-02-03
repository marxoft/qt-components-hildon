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
    \class DatePickSelector
    \brief A pick selector for choosing a date value.
    
    \ingroup components
    
    \snippet selectors.qml DatePickSelector
    
    \sa ListPickSelector, TimePickSelector, ValueButton
*/  
AbstractPickSelector {
    id: root
    
    /*!
        \brief The currently displayed year.
        
        The default value is the current year.
    */
    property int year: dateTime.currentYear()
    
    /*!
        \brief The currently displayed month.
        
        The default value is the current month.
    */
    property int month: dateTime.currentMonth()
    
    /*!
        \brief The currently displayed day.
        
        The default value is the current day.
    */
    property int day: dateTime.currentDay()
    
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
        \brief The format used for the date value text.
        
        The default value is \c "ddd, d MMMM yyyy".
    */
    property variant valueTextFormat: "ddd, d MMMM yyyy"
    
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
            id: dayView
                            
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: ListModel {
                id: dayModel
            }
            delegate: defaultDelegate
        }
        
        ListView {
            id: monthView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: ListModel {
                id: monthModel
            }
            delegate: defaultDelegate
            onCurrentIndexChanged: if (internal.ready) internal.updateDays();
        }
        
        ListView {
            id: yearView
                
            width: Math.floor((parent.width - parent.spacing) / 3)
            height: parent.height
            model: ListModel {
                id: yearModel
            }
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
            internal.updateValueText();
            root.selected(root.currentValueText);
        }
    }
    
    QtObject {
        id: internal
        
        property bool ready: false
        
        function init() {
            // Script values cannot be used with ListElement
            for (var i = 1; i <= 12; i++) {
                monthModel.append({name: dateTime.longMonthName(i), value: i});
            }
            
            updateYears();
            updateDays();
            updateYear();
            updateMonth();
            updateDay();
            updateValueText();
            ready = true;
        }
        
        function reset() {
            updateYear();
            updateMonth();
            updateDay();
        }
        
        function updateYear() {
            yearView.currentIndex = root.year - root.minimumYear;
        }
        
        function updateMonth() {
            monthView.currentIndex = root.month - 1;
        }
        
        function updateDay() {
            dayView.currentIndex = root.day - 1;
        }
        
        function updateDays() {
            var count = dayModel.count;
            var days = dateTime.daysInMonth(yearModel.get(yearView.currentIndex).value,
                                            monthModel.get(monthView.currentIndex).value);
            
            if (count > days) {
                if (dayView.currentIndex >= days) {
                    dayView.currentIndex = days - 1;
                }
                
                while (count > days) {
                    count--;
                    dayModel.remove(count);
                }
            }
            else {
                while (count < days) {
                    count++;
                    dayModel.append({name: count, value: count});
                }
            }
        }
        
        function updateYears() {
            var start = root.minimumYear;
            var end = root.maximumYear;
            yearModel.clear();
            
            while (start <= end) {
                var year = start++;
                yearModel.append({name: year, value: year});
            }
        }
        
        function updateValueText() {
            root.year = yearModel.get(yearView.currentIndex).value;
            root.month = monthModel.get(monthView.currentIndex).value;
            root.day = dayModel.get(dayView.currentIndex).value;
            root.currentValueText = Qt.formatDate(dateTime.date(root.year, root.month, root.day), root.valueTextFormat);
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
    
    onYearChanged: if (internal.ready) internal.updateYear();
    onMonthChanged: if (internal.ready) internal.updateMonth();
    onDayChanged: if (internal.ready) internal.updateDay();
    onMinimumYearChanged: if (internal.ready) internal.updateYears();
    onMaximumYearChanged: if (internal.ready) internal.updateYears();
    onRejected: if (internal.ready) internal.reset();
    onSelected: accept()
}
