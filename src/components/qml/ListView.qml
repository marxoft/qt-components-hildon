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

ListView {
    id: root        
    
    property int navigationMode: NavigationMode.TouchNavigation
    property int horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
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
