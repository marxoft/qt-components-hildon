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
    \class ToolBar
    \brief A container for ToolButton and other items.
    
    \ingroup components
    
    \sa ToolBarStyle, ToolButton
*/
Item {
    id: root
    
    default property alias tools: row.data
    
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
        
        anchors.fill: parent
        spacing: root.style.spacing
    }
}
