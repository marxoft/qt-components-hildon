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
import org.hildon.components 1.0

/*!
    \class ListView
    \brief A standard QtQuick ListView element with scroll bars.
    
    \ingroup components
    
    The ListView component behaves in the same way as the standard QtQuick ListView element, but with optional 
    scroll bars.
    
    \sa ListItem, ScrollBar
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
    
    contentItem.width: width - ((verticalScrollBarPolicy == Qt.ScrollBarAlwaysOff) || (contentHeight < height)
                                ? 0 : verticalScrollBar.style.scrollBarWidth)
    
    contentItem.height: height - ((horizontalScrollBarPolicy == Qt.ScrollBarAlwaysOff) || (contentWidth < width)
                                  ? 0 : horizontalScrollBar.style.scrollBarWidth)
    
    focus: true  
    interactive: (contentWidth > width) || (contentHeight > height)
    
    ScrollBar {
        id: horizontalScrollBar
    
        flickableItem: root
        orientation: Qt.Horizontal
        scrollBarPolicy: root.horizontalScrollBarPolicy
    }
        
    ScrollBar {
        id: verticalScrollBar
    
        flickableItem: root
        orientation: Qt.Vertical
        scrollBarPolicy: root.verticalScrollBarPolicy
    }
}
