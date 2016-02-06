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
    \class ListPickSelector
    \brief A pick selector used for selecting an item from a list.
    
    \ingroup components
    
    \snippet selectors.qml ListPickSelector
    
    \sa DatePickSelector, TimePickSelector, ValueButton
*/
AbstractPickSelector {
    id: root
    
    /*!
        type:variant
        \brief The model to be used by the view.
    */
    property alias model: view.model
    
    /*!
        type:int
        \brief The current number of items in the view.
    */
    property alias count: view.count
    
    /*!
        \brief The current chosen index in the view.
    */
    property int currentIndex
    
    /*!
        \brief The name of the role that provides the text to be displayed in the delegate.
    */
    property string textRole
    
    height: 360
    
    ListView {
        id: view
        
        property bool modelIsArray: false
        
        anchors.fill: parent
        focus: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        navigationMode: NavigationMode.KeyNavigation
        delegate: defaultDelegate
        onModelChanged: modelIsArray = !!model ? model.constructor === Array : false
    }
    
    Component {
        id: defaultDelegate
        
        ListItem {
            id: item
            
            property alias text: label.text
            
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
                text: root.textRole === "" ?  modelData
                      : ((view.modelIsArray ? modelData[root.textRole] : model[root.textRole]) || "")
            }
            onClicked: {
                root.currentIndex = index;
                root.selected(text);
            }
        }
    }
    
    onStatusChanged: if (status == DialogStatus.Opening) view.currentIndex = currentIndex;
    onCurrentIndexChanged: {
        if (currentIndex != view.currentIndex) {
            view.currentIndex = currentIndex;
        }
        
        if (view.currentItem) {
            currentValueText = view.currentItem.text;
        }
    }
    onSelected: accept()
    
    Component.onCompleted: {
        if (currentIndex != view.currentIndex) {
            view.currentIndex = currentIndex;
        }
        
        if (view.currentItem) {
            currentValueText = view.currentItem.text;
        }
    }
}
