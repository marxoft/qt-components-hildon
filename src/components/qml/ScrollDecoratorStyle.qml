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
    \class ScrollDecoratorStyle
    \brief Provides styling properties for a ScrollDecorator.
    
    \ingroup components
    
    \sa ScrollDecorator
*/
Style {
    /*!
        \brief The color of the ScrollDecorator.
    */
    property color scrollBarColor: platformStyle.secondaryTextColor
    
    /*!
        \brief The width of the ScrollDecorator.
    */
    property int scrollBarWidth: platformStyle.paddingMedium
}
