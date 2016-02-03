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
    \class OssoComboBoxStyle
    \brief Provides Osso styling properties for a ComboBox.
    
    \ingroup components
    
    \sa ComboBox
*/
ComboBoxStyle {
    background: "image://theme/combobox_frame_normal"
    backgroundDisabled: "image://theme/combobox_frame_disabled"
    backgroundSelected: "image://theme/combobox_frame_normal"
    
    button: "image://theme/combobox_button_normal"
    buttonDisabled: "image://theme/combobox_button_disabled"
    buttonSelected: "image://theme/combobox_button_pressed"
    
    textInputBackground: "image://theme/combobox_entry_normal"
    textInputBackgroundDisabled: "image://theme/combobox_entry_disabled"
    textInputBackgroundSelected: "image://theme/combobox_entry_focused"
    
    textInputButton: "image://theme/combobox_entry_button_normal"
    textInputButtonDisabled: "image://theme/combobox_entry_button_disabled"
    textInputButtonSelected: "image://theme/combobox_entry_button_pressed"
    
    backgroundMarginLeft: 14
    backgroundMarginRight: 14
    backgroundMarginTop: 14
    backgroundMarginBottom: 14
    
    icon: "image://theme/combobox_arrow_normal"
    iconDisabled: "image://theme/combobox_arrow_disabled"
    iconPressed: "image://theme/combobox_arrow_pressed"
    
    textInputIcon: "image://theme/combobox_entry_arrow_normal"
    textInputIconDisabled: "image://theme/combobox_entry_arrow_disabled"
    textInputIconPressed: "image://theme/combobox_entry_arrow_pressed"
    
    textColor: platformStyle.defaultTextColor
    
    paddingLeft: platformStyle.paddingMedium
    paddingRight: platformStyle.paddingMedium
    
    buttonWidth: 48
    defaultHeight: 48
    
    listViewStyle: OssoListViewStyle {}
    listItemStyle: OssoListItemStyle {}
}
