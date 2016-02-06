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
    \class ToolBar
    \brief A container for ToolButton and other items.
    
    \ingroup components
    
    \sa ToolBarStyle, ToolButton
*/
Item {
    id: root
    
    default property alias tools: row.data
    
    /*!
        type:enumeration
        \brief The horizontal alignment of the items in the tool bar.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.AlignLeft</td>
                <td>Items are aligned to the left (default).</td>
            </tr>
            <tr>
                <td>Qt.AlignHCenter</td>
                <td>Items are aligned centrally.</td>
            </tr>
            <tr>
                <td>Qt.AlignRight</td>
                <td>Items are aligned to the right.</td>
            </tr>
        </table>
    */
    property int alignment: Qt.AlignLeft
    /*!
        type:int
        \brief The space between each item in the tool bar.
        
        The default value is \c 0.
    */
    property alias spacing: row.spacing
    
    /*!
        type:ToolBarStyle
        \brief Provides styling properties for the tool bar.
    */
    property QtObject style: ToolBarStyle {}
    
    width: screen.width
    height: 70
    
    MouseArea {
        anchors.fill: parent
    }
    
    Image {
        id: background
        
        anchors.fill: parent
        source: root.style.background
        smooth: true
    }
    
    Row {
        id: row
        
        property bool complete: false
        
        function positionTools() {
            if (!complete) {
                return;
            }
            
            for (var i = 0; i < children.length; i++) {
                var child = children[i];
                
                if (child.height < height) {
                    child.y = Math.floor((height - child.height) / 2);
                }
            }
        }
        
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        
        states: [
            State {
                name: "AlignHCenter"
                when: root.alignment == Qt.AlignHCenter
                
                AnchorChanges {
                    target: row
                    anchors {
                        left: undefined
                        horizontalCenter: parent.horizontalCenter
                    }
                }
            },
            
            State {
                name: "AlignRight"
                when: root.alignment == Qt.AlignRight
                
                AnchorChanges {
                    target: row
                    anchors {
                        left: undefined
                        right: parent.right
                    }
                }
            }
        ]
        
        onChildrenChanged: positionTools()
        onHeightChanged: positionTools()
    }
    
    Component.onCompleted: {
        row.complete = true;
        row.positionTools();
    }
}
