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
    \class LabelStyle
    \brief Provides styling properties for a Label.
    
    \ingroup components
    
    \sa Label
*/
Style {
    // Color
    
    /*!
        \brief The text color.
    */
    property color textColor: platformStyle.defaultTextColor

    // Font
    
    /*!
        \brief The font family.
    */
    property string fontFamily
    
    /*!
        \brief The font point size.
    */
    property int fontPointSize: platformStyle.fontSizeMedium
}
