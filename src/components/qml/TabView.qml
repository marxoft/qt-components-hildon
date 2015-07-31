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

Item {
    id: root
    
    default property alias tabs: tabItem.children
    
    property bool tabsVisible: true
    property int currentIndex
    
    Component {
        id: tabBarComponent
        
        Row {
            id: tabBar
            
            Repeater {
                id: repeater
                
                model: tabItem.children
                
                TabButton {
                    text: modelData.title
                    checked: root.currentIndex == index
                    onClicked: root.currentIndex = index
                }
            }
        }
    }
    
    Loader {
        id: tabBarLoader
        
        height: 35
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        sourceComponent: root.tabsVisible ? tabBarComponent : undefined
    }
    
    Item {
        id: tabItem
                
        anchors {
            left: parent.left
            right: parent.right
            top: tabBarLoader.item ? tabBarLoader.bottom : parent.top
            bottom: parent.bottom
        }
    }
    
    onCurrentIndexChanged: {
        for (var i = 0; i < tabItem.children.length; i++) {
            tabItem.children.visible = (i == currentIndex);
        }
    }
}
