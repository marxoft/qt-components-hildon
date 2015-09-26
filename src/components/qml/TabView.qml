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
    \class TabView
    \brief A container used for switching between items.
    
    \ingroup components
    
    \snippet tabs.qml TabView
    
    \sa Tab, TabButton
*/
FocusScope {
    id: root
    
    default property alias tabs: tabItem.children
    
    /*!
        \brief Whether the tab buttons should be visible.
        
        The default value is \c true.
    */
    property bool tabsVisible: true
    
    /*!
        \brief The index of the currently visible Tab.
    */
    property int currentIndex
    
    Component {
        id: tabBarComponent
        
        Item {
            id: tabBar
            
            height: 35
            
            ExclusiveGroup {
                id: tabButtonGroup
            }
            
            TabButtonStyle {
                id: tabButtonStyle
            }
        
            Row {            
                anchors.fill: parent
            
                Repeater {
                    id: repeater
                
                    model: tabItem.children
                
                    Button {
                        text: modelData.title
                        checkable: true
                        checked: root.currentIndex == index
                        exclusiveGroup: tabButtonGroup
                        style: tabButtonStyle
                        onPressedChanged: if (pressed) root.currentIndex = index;
                    }
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
        
        onChildrenChanged: {
            var index = children.length - 1;
            children[index].visible = (index == root.currentIndex);
        }
    }
    
    onCurrentIndexChanged: {
        for (var i = 0; i < tabItem.children.length; i++) {
            tabItem.children[i].visible = (i == currentIndex);
        }
    }
}
