/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

import org.hildon.components 1.0

Page {
    id: root

    windowTitle: qsTr("ListView")
    
    Column {
        id: column
        
        anchors {
            fill: parent
            margins: platformStyle.paddingMedium
        }

        ListView {
            id: view

            width: parent.width
            horizontalScrollMode: ListView.ScrollPerItem
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            model: SortFilterProxyModel {
                id: proxyModel
                
                sourceModel: [
                    { 
                        "name": qsTr("Red"),
                        "color": "red"
                    },
                    
                    { 
                        "name": qsTr("Yellow"),
                        "color": "yellow"
                    },
                    
                    { 
                        "name": qsTr("Pink"),
                        "color": "pink"
                    },
                    
                    { 
                        "name": qsTr("Green"),
                        "color": "green"
                    },
                    
                    { 
                        "name": qsTr("Purple"),
                        "color": "purple"
                    },
                    
                    { 
                        "name": qsTr("Orange"),
                        "color": "orange"
                    },
                    
                    { 
                        "name": qsTr("Blue"),
                        "color": "blue"
                    }
                ]
                dynamicSortFilter: true
                filterProperty: "name"
                filterRegExp: filterEdit.text ? eval("(/" + filterEdit.text + "/i)") : /^/
            }
            delegate: ListItem {
                width: view.width
                height: 70

                ListItemImage {
                    anchors.fill: parent
                    source: "image://theme/TouchListBackground" + (isCurrentItem ? "Pressed" : "Normal")
                }

                ListItemRectangle {
                    id: rect
                    
                    width: 56
                    height: 56
                    anchors {
                        left: parent.left
                        leftMargin: platformStyle.paddingMedium
                        verticalCenter: parent.verticalCenter
                    }
                    radius: 4
                    color: modelData.color
                    smooth: true
                }
                
                ListItemLabel {
                    id: label
                    
                    anchors {
                        left: rect.right
                        right: parent.right
                        top: parent.top
                        bottom: parent.bottom
                        margins: platformStyle.paddingMedium
                    }
                    alignment: Qt.AlignVCenter
                    text: modelData.name
                }
            }
        }
        
        ToolBar {
            id: toolBar
            
            visible: false
            movable: false
            
            TextField {
                id: filterEdit
                
                onTextChanged: if (text) toolBar.visible = true;
            }
            
            Action {
                icon: "general_close"
                onTriggered: toolBar.visible = false
            }
            
            onVisibleChanged: {
                if (visible) {
                    filterEdit.focus = true;
                }
                else {
                    filterEdit.clear();
                }
            }
        }
    }
    
    Keys.onPressed: if ((!filterEdit.focus) && (!/^\s/.test(event.text))) filterEdit.text += event.text;
}
