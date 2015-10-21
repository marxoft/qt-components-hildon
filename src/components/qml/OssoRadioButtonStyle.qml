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
    \class OssoRadioButtonStyle
    \brief Provides Osso radio button styling properties for RadioButton.
    
    \ingroup components
        
    \sa RadioButton
*/
RadioButtonStyle {
    background: ""
    backgroundChecked: ""
    backgroundDisabled: ""
    backgroundPressed: ""
    icon: "image://theme/qgn_plat_button_radio_empty_normal"
    iconChecked: "image://theme/qgn_plat_button_radio_selected_normal"
    iconCheckedDisabled: "image://theme/qgn_plat_button_radio_selected_disabled"
    iconCheckedPressed: "image://theme/qgn_plat_button_radio_selected_focused"
    iconDisabled: "image://theme/qgn_plat_button_radio_empty_disabled"
    iconPressed: "image://theme/qgn_plat_button_radio_empty_focused"
    iconWidth: 26
    iconHeight: 26
    paddingLeft: 0
}
