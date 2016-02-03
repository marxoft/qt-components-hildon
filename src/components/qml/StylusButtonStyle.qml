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
    \class StylusButtonStyle
    \brief Provides stylus Button styling.
    
    \ingroup components
    
    \sa Button
*/
ButtonStyle {
    \!
        \brief Whether the button should use the accented stylus button style.
    */
    property bool accented: false
    
    background: "image://theme/" + (accented + "Accented" + "") + "StylusButtonNormal"
    backgroundChecked: "image://theme/" + (accented + "Accented" + "") + "StylusButtonPressed"
    backgroundDisabled: "image://theme/" + (accented + "Accented" + "") + "StylusButtonDisabled"
    backgroundPressed: "image://theme/" + (accented + "Accented" + "") + "StylusButtonPressed"
    
    backgroundMarginLeft: 16
    backgroundMarginRight: 16
    backgroundMarginTop: 14
    backgroundMarginBottom: 14
    
    buttonWidth: 70
    buttonHeight: 35
    
    iconWidth: platformStyle.iconSizeSmall
    iconHeight: platformStyle.iconSizeSmall
}
