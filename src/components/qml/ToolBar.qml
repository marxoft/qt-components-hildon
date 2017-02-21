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
    
    default property alias tools: grid.data
    
    /*!
        type:flags
        \brief The alignment of the items in the tool bar.
        
        The alignment can be a bitwise OR combination of:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.AlignLeft</td>
                <td>Items are horizontally aligned to the left (default).</td>
            </tr>
            <tr>
                <td>Qt.AlignHCenter</td>
                <td>Items are horizontally aligned centrally.</td>
            </tr>
            <tr>
                <td>Qt.AlignRight</td>
                <td>Items are horizontally aligned to the right.</td>
            </tr>
            <tr>
                <td>Qt.AlignTop</td>
                <td>Items are vertically aligned to the top (default).</td>
            </tr>
            <tr>
                <td>Qt.AlignVCenter</td>
                <td>Items are vertically aligned centrally.</td>
            </tr>
            <tr>
                <td>Qt.AlignBottom</td>
                <td>Items are vertically aligned to the bottom.</td>
            </tr>
        </table>
    */
    property int alignment: Qt.AlignLeft | Qt.AlignTop
    
    /*!
        type:enumeration
        \brief The orientation of the tool bar.
        
        The orientation can be either Qt.Horizontal (the default) or Qt.Vertical.
    */
    property int orientation: Qt.Horizontal
    
    /*!
        type:int
        \brief The space between each item in the tool bar.
        
        The default value is \c 0.
    */
    property alias spacing: grid.spacing
    
    /*!
        type:ToolBarStyle
        \brief Provides styling properties for the tool bar.
    */
    property QtObject style: ToolBarStyle {}
    
    /*!
        \fn ToolButton ToolBar::addAction(Action action)
        \brief Creates and adds a ToolButton with the specifed \a action and returns it.
        @param action
        @return ToolButton
    */
    
    /*!
        \fn ToolButton ToolBar::addAction(string iconName, string text)
        \brief Creates and adds a ToolButton with the specifed \a iconName and \a text and returns it.
        @param iconName
        @param text
        @return ToolButton
    */
    
    function addAction() {
        var button = buttonComponent.createObject(grid);
        
        if (Qt.isQtObject(arguments[0])) {
            button.action = arguments[0];
        }
        else {
            if (typeof arguments[0] === "string") {
                button.iconName = arguments[0];
            }
            
            if (typeof arguments[1] === "string") {
                button.text = arguments[1];
            }
        }
        
        return button;
    }
    
    /*!
        \brief Adds the specified \a item to the tool bar.
        @param type:Item item
    */
    function addItem(item) {
        grid.addItem(item);
    }
    
    /*!
        \fn ToolButton ToolBar::insertAction(Action action)
        \brief Creates and inserts a ToolButton with the specifed \a action at \a index and returns it.
        @param action
        @return ToolButton
    */
    
    /*!
        \fn ToolButton ToolBar::insertAction(string iconName, string text)
        \brief Creates and inserts a ToolButton with the specifed \a iconName and \a text at \a index and returns it.
        @param iconName
        @param text
        @return ToolButton
    */
    
    function insertAction() {
        var button = buttonComponent.createObject(null);
        
        if (Qt.isQtObject(arguments[1])) {
            button.action = arguments[1];
        }
        else {
            if (typeof arguments[1] === "string") {
                button.iconName = arguments[1];
            }
            
            if (typeof arguments[2] === "string") {
                button.text = arguments[2];
            }
        }
        
        grid.insertItem(arguments[0], button);
        return button;
    }
    
    /*!
        \brief Inserts the specified \a item into the tool bar at \a index.
        @param type:int index
        @param type:Item item
    */
    function insertItem(index, item) {
        grid.insertItem(index, item);
    }
    
    /*!
        \brief Returns the item at the specified \a index, or \c null if \a index is out of range.
        @param type:int index
        @return type:Item
    */
    function itemAt(index) {
        return grid.itemAt(index);
    }
    
    /*!
        \brief Removes the specified \a item from the tool bar and sets its parent to \c null.
    */
    function removeItem(item) {
        grid.removeItem(item);
    }
    
    width: orientation == Qt.Vertical ? 70 : screen.width
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
    
    GridLayout {
        id: grid
        
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        columns: root.orientation == Qt.Vertical ? 1 : children.length
    }
    
    Component {
        id: buttonComponent
        
        ToolButton {}
    }
    
    onAlignmentChanged: {
        if (alignment & Qt.AlignLeft) {
            grid.anchors.horizontalCenter = undefined;
            grid.anchors.right = undefined;
            grid.anchors.left = left;
        }
        else if (alignment & Qt.AlignRight) {
            grid.anchors.left = undefined;
            grid.anchors.horizontalCenter = undefined;
            grid.anchors.right = right;
        }
        else if (alignment & Qt.AlignHCenter) {
            grid.anchors.left = undefined;
            grid.anchors.right = undefined;
            grid.anchors.horizontalCenter = horizontalCenter;
        }
        
        if (alignment & Qt.AlignTop) {
            grid.anchors.verticalCenter = undefined;
            grid.anchors.bottom = undefined;
            grid.anchors.top = top;
        }
        else if (alignment & Qt.AlignBottom) {
            grid.anchors.top = undefined;
            grid.anchors.verticalCenter = undefined;
            grid.anchors.bottom = bottom;
        }
        else if (alignment & Qt.AlignVCenter) {
            grid.anchors.top = undefined;
            grid.anchors.bottom = undefined;
            grid.anchors.verticalCenter = verticalCenter;
        }
    }
}
