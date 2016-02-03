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
    \class Label
    \brief A text label with standard font properties.
    
    \ingroup components
    
    \sa LabelStyle
*/
Text {
    id: root
    
    /*!
        type:LabelStyle
        \brief Provides styling properties for the label.
    */
    property QtObject style: LabelStyle {}
    
    color: style.textColor
    font.pointSize: Math.max(1, style.fontPointSize)
}
