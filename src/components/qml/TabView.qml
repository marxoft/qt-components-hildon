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

/*!
    \class TabView
    \brief A container used for switching between items.
    
    \ingroup components
    
    \snippet tabs.qml TabView
    
    \sa Tab, TabBar, TabButton
*/
FocusScope {
    id: root
    
    /*!
        type:list<Item>
        \brief The tabs belonging to the tab view.
    */
    default property alias tabs: tabItem.children
    
    /*!
        type:Item
        \brief The container for the tabs.
    */
    property alias contentItem: tabItem
    
    /*!
        \brief The current tab count.
    */
    property int count
    
    /*!
        \brief The index of the currently visible Tab.
    */
    property int currentIndex
    
    /*!
        \brief The currently visible tab, or \c null if no tab is visible.
    */
    property Item currentTab
    
    /*!
        \brief Whether the frame should be visible
        
        The default value is \c true.
    */
    property bool frameVisible: true
    
    /*!
        \brief Whether the tab bar should be visible.
        
        The default value is \c true.
    */
    property bool tabBarVisible: true
    
    /*!
        \brief Adds a new tab with \a title and optional \a Component.
        
        Returns the newly added tab.
        
        @param type:string title
        @param type:Component component
        @return type:Item
    */
    function addTab(title, component) {
        if (!component) {
            component = tabComponent;
        }
        
        return component.createObject(tabItem, {title: title});
    }
    
    /*!
        \brief Returns the tab at \a index.
        @param type:int index
        @return type:Item
    */
    function getTab(index) {
        return tabItem.children[index];
    }
    
    /*!
        \brief Removes and destroys a tab at the given \a index.
        @param type:int index
    */
    function removeTab(index) {
        var tab = tabItem.children[index];
        
        if (tab) {
            if (index == currentIndex) {
                currentIndex = Math.max(0, currentIndex - 1);
            }

            tab.destroy();
        }
    }
    
    Component {
        id: tabComponent
        
        Tab {}
    }
    
    Component {
        id: tabBarComponent
        
        TabBar {
            model: tabItem.children
            onCurrentIndexChanged: if (root.currentIndex != currentIndex) root.currentIndex = currentIndex;
            Component.onCompleted: currentIndex = root.currentIndex
        }
    }
    
    Loader {
        id: tabBarLoader
        
        z: 1000
        anchors {
            left: parent.left
            leftMargin: platformStyle.paddingMedium
            right: parent.right
            rightMargin: platformStyle.paddingMedium
            top: parent.top
        }
        sourceComponent: root.tabBarVisible ? tabBarComponent : undefined
    }
    
    BorderImage {
        id: tabItem
        
        property bool completed: false
                
        function currentIndexChanged() {
            if (!completed) {
                return;
            }
                        
            if ((tabBarLoader.item) && (tabBarLoader.item.currentIndex != root.currentIndex)) {
                tabBarLoader.item.currentIndex = root.currentIndex;
            }
            
            updateCurrentTab();
        }

        function updateCurrentTab() {
            if (!completed) {
                return;
            }
            
            var index = Math.min(root.currentIndex, children.length - 1);

            if (index == -1) {
                root.currentTab = null;
                return;
            }
                        
            for (var i = 0; i < children.length; i++) {
                var tab = children[i];

                if (i == index) {
                    tab.visible = true;
                    tab.forceActiveFocus();
                    root.currentTab = tab;
                }
                else {
                    tab.visible = false;
                }
            }
        }
             
        anchors {
            left: parent.left
            right: parent.right
            top: tabBarLoader.item ? tabBarLoader.bottom : parent.top
            bottom: parent.bottom
        }
        border {
            left: 8
            right: 8
            top: 8
            bottom: 8
        }
        smooth: true
        source: root.frameVisible ? "image://theme/qgn_plat_notebook_tab_area_border" : ""        
        onChildrenChanged: {
            root.count = children.length;
            updateCurrentTab();
        }
    }
    
    onCurrentIndexChanged: tabItem.currentIndexChanged()
    
    Component.onCompleted: {
        tabItem.completed = true;
        tabItem.currentIndexChanged();
    }
}
