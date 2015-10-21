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
    \class FlickableStyle
    \brief Provides styling properties for a Flickable.
    
    \ingroup components
    
    \sa Flickable, OssoFlickableStyle
*/
Style {
    /*!
        \brief Whether the Flickable should be interactive (use kinetic scrolling).
    */
    property bool interactive: true
    
    /*!
        \brief The component used for the Flickable's scroll bar.
    */
    property Component scrollBar: ScrollDecorator {}
}
