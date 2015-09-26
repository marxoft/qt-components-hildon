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
    \class Tab
    \brief A Loader for use in a TabView.
    
    \ingroup components
    
    \snippet tabs.qml TabView
    
    \sa TabView
*/
Loader {
    /*!
        \brief Whether the tab should load its content immediately.
        
        The default value is \c false.
    */
    property bool active: false
    
    /*!
        \brief The text that will be displayed in the tab button.
    */
    property string title
    
    default property Component component
    
    anchors.fill: parent ? parent : undefined
    visible: false
    
    onActiveChanged: if ((active) && (component)) sourceComponent = component;
    onComponentChanged: if ((component) && (active)) sourceComponent = component;
    onVisibleChanged: if (visible) active = true;
}
