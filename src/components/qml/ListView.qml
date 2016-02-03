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

/*!
    \class ListView
    \brief A standard QtQuick ListView element with scroll bars.
    
    \ingroup components
    
    The ListView component behaves in the same way as the standard QtQuick ListView element, but with optional 
    scroll bars.
    
    \sa ListItem, ListViewStyle, OssoListViewStyle
*/
ListView {
    id: root        
    
    /*!
        type:enumeration
        \brief The current navigation mode used by the view
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>NavigationMode.TouchNavigation</td>
                <td>The view is navigated using touch (default).</td>
            </tr>
            <tr>
                <td>NavigationMode.KeyNavigation</td>
                <td>The view is navigated using key presses.</td>
            </tr>
        </table>
    */
    property int navigationMode: NavigationMode.TouchNavigation
    
    /*!
        type:enumeration
        \brief The policy used to determine whether the horizontal scroll bar should be visible.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.ScrollBarAlwaysOn</td>
                <td>The horizontal scroll bar should always be visible.</td>
            </tr>
            <tr>
                <td>Qt.ScrollBarAlwaysOff</td>
                <td>The horizontal scroll bar should never be visible.</td>
            </tr>
            <tr>
                <td>Qt.ScrollBarAsNeeded</td>
                <td>The horizontal scroll bar should be visible when the content width is greater than the width of the
                view (default).</td>
            </tr>
        </table>
    */
    property int horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
    
    /*!
        type:enumeration
        \brief The policy used to determine whether the vertical scroll bar should be visible.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.ScrollBarAlwaysOn</td>
                <td>The vertical scroll bar should always be visible.</td>
            </tr>
            <tr>
                <td>Qt.ScrollBarAlwaysOff</td>
                <td>The vertical scroll bar should never be visible.</td>
            </tr>
            <tr>
                <td>Qt.ScrollBarAsNeeded</td>
                <td>The vertical scroll bar should be visible when the content height is greater than the height of the
                view (default).</td>
            </tr>
        </table>
    */
    property int verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
    
    /*!
        type:FlickableStyle
        \brief Provides styling properties for the flickable.        
    */
    property QtObject style: FlickableStyle {}
    
    focus: true
    highlightMoveDuration: 1
    interactive: (root.style.interactive) && ((contentWidth > width) || (contentHeight > height))
    
    QtObject {
        id: internal
        
        property bool complete: false
                
        property Item horizontalScrollBar
        property Item verticalScrollBar
        
        function setHorizontalScrollBar() {
            if (!complete) {
                return;
            }
            
            switch (root.horizontalScrollBarPolicy) {
            case Qt.ScrollBarAlwaysOn: {
                if (!horizontalScrollBar) {
                    horizontalScrollBar = root.style.scrollBar.createObject(root, {flickableItem: root,
                                                                            orientation: Qt.Horizontal});
                }
                else {
                    horizontalScrollBar.visible = true;
                }
                
                root.contentItem.height = root.height - horizontalScrollBar.style.scrollBarWidth;
                break;
            }
            case Qt.ScrollBarAlwaysOff: {
                if (horizontalScrollBar) {
                    horizontalScrollBar.visible = false;
                }
                
                root.contentItem.height = root.height;
                break;
            }
            default: {
                if (root.contentWidth > root.width) {
                    if (!horizontalScrollBar) {
                        horizontalScrollBar = root.style.scrollBar.createObject(root, {flickableItem: root,
                                                                                orientation: Qt.Horizontal});
                    }
                    else {
                        horizontalScrollBar.visible = true;
                    }
                    
                    root.contentItem.height = root.height - horizontalScrollBar.style.scrollBarWidth;
                }
                else {
                    if (horizontalScrollBar) {
                        horizontalScrollBar.visible = false;
                    }
                    
                    root.contentItem.height = root.height;
                }
                                
                break;
            }
            }
        }
        
        function setVerticalScrollBar() {
            if (!complete) {
                return;
            }
            
            switch (root.verticalScrollBarPolicy) {
            case Qt.ScrollBarAlwaysOn: {
                if (!verticalScrollBar) {
                    verticalScrollBar = root.style.scrollBar.createObject(root, {flickableItem: root,
                                                                          orientation: Qt.Vertical});
                }
                else {
                    verticalScrollBar.visible = true;
                }
                
                root.contentItem.width = root.width - verticalScrollBar.style.scrollBarWidth;
                break;
            }
            case Qt.ScrollBarAlwaysOff: {
                if (verticalScrollBar) {
                    verticalScrollBar.visible = false;
                }
                
                root.contentItem.width = root.width;
                break;
            }
            default: {
                if (root.contentHeight > root.height) {
                    if (!verticalScrollBar) {
                        verticalScrollBar = root.style.scrollBar.createObject(root, {flickableItem: root,
                                                                              orientation: Qt.Vertical});
                    }
                    else {
                        verticalScrollBar.visible = true;
                    }
                    
                    root.contentItem.width = root.width - verticalScrollBar.style.scrollBarWidth;
                }
                else {
                    if (verticalScrollBar) {
                        verticalScrollBar.visible = false;
                    }
                    
                    root.contentItem.width = root.width;
                }
                
                break;
            }
            }
        }
    }
    
    onContentWidthChanged: internal.setHorizontalScrollBar()
    onWidthChanged: internal.setHorizontalScrollBar()
    onHorizontalScrollBarPolicyChanged: internal.setHorizontalScrollBar()
    
    onContentHeightChanged: internal.setVerticalScrollBar()
    onHeightChanged: internal.setVerticalScrollBar()
    onVerticalScrollBarPolicyChanged: internal.setVerticalScrollBar()
    
    Component.onCompleted: {
        internal.complete = true;
        internal.setHorizontalScrollBar();
        internal.setVerticalScrollBar();
    }
}
