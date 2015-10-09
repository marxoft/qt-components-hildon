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
    \class TabBar
    \brief A row of TabButton.
    
    \ingroup components
    
    \snippet tabs.qml TabBar
    
    \sa Tab, TabButton, TabView
*/
FocusScope {
    id: root
    
    /*!
        \brief The index of the currently selected tab button.
    */
    property int currentIndex
    
    /*!
        type:int
        \brief The number of tabs in the tab bar.
    */
    property alias count: view.count
    
    /*!
        type:variant
        \brief The model used to display tab buttons in the tab bar.
    */
    property alias model: view.model
    
    /*!
        \brief The name of the role that provides the text to be displayed in the tab buttons.
    */
    property string textRole
    
    height: 35 + platformStyle.paddingSmall
    
    Keys.onLeftPressed: if (currentIndex > 0) currentIndex -= 1;
    Keys.onRightPressed: if (currentIndex < (count - 1)) currentIndex += 1;
    
    ListView {
        id: view
        
        property bool completed: false
        property bool modelIsArray: false
        
        anchors {
            left: parent.left
            leftMargin: buttonsLoader.item ? 20 : 0
            right: parent.right
            rightMargin: buttonsLoader.item ? 20 : 0
            top: parent.top
            bottom: parent.bottom
        }
        clip: true
        enabled: root.enabled
        interactive: false
        orientation: ListView.Horizontal
        delegate: Item {
            width: button.width
            height: root.height
            
            Button {
                id: button
                
                anchors.bottom: parent.bottom
                enabled: root.enabled
                style: TabButtonStyle {
                    background: "image://theme/qgn_plat_notebook_tab_"
                                + (root.currentIndex == index ? "active" : "passive")
                    buttonHeight: root.height - (root.currentIndex == index ? 0 : platformStyle.paddingSmall)
                }
                text: root.textRole === "" ?  modelData.title ? modelData.title : modelData
                      : ((view.modelIsArray ? modelData[root.textRole] : model[root.textRole]) || "")
                onPressedChanged: if (pressed) root.currentIndex = index;
            }
        }
        onModelChanged: {
            modelIsArray = !!model ? model.constructor === Array : false;
            currentIndex = Math.min(root.currentIndex, count - 1);
            root.currentIndex = currentIndex;
        }
        onContentWidthChanged: {
            if (completed) {
                buttonsLoader.sourceComponent = (contentWidth > width ? buttonsComponent : undefined);
            }
        }
        
        Component.onCompleted: {
            completed = true;
            buttonsLoader.sourceComponent = (contentWidth > width ? buttonsComponent : undefined);
        }        
    }
    
    Loader {
        id: buttonsLoader
        
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
    }
    
    Component {
        id: buttonsComponent
        
        Row {
            spacing: width - 40
            
            Button {
                enabled: root.enabled
                style: ButtonStyle {
                    buttonWidth: 20
                    buttonHeight: 30
                    background: "image://theme/qgn_plat_notebook_button_previous"
                    backgroundDisabled: "image://theme/qgn_plat_notebook_button_previous_disabled"
                    backgroundPressed: "image://theme/qgn_plat_notebook_button_previous_pressed"
                }
                onClicked: if (root.currentIndex > 0) root.currentIndex -= 1;
            }
            
            Button {
                enabled: root.enabled
                style: ButtonStyle {
                    buttonWidth: 20
                    buttonHeight: 30
                    background: "image://theme/qgn_plat_notebook_button_next"
                    backgroundDisabled: "image://theme/qgn_plat_notebook_button_next_disabled"
                    backgroundPressed: "image://theme/qgn_plat_notebook_button_next_pressed"
                }
                onClicked: if (root.currentIndex < root.count - 1) root.currentIndex += 1;
            }
        }
    }
    
    onCurrentIndexChanged: if (view.currentIndex != currentIndex) view.currentIndex = currentIndex;
}
