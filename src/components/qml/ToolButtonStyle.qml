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
    \class ToolButtonStyle
    \brief Provides custom styling properties for a ToolButton.
    
    \ingroup components
    
    \sa ToolButtonStyle
*/
ButtonStyle {
    // ToolButton style
    
    /*!
        type:enumeration
        \brief Specifies the layout used for the ToolButton text and icon.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>Qt.ToolButtonIconOnly</td>
                <td>Only display the icon (default).</td>
            </tr>
            <tr>
                <td>Qt.ToolButtonTextOnly</td>
                <td>Only display the text.</td>
            </tr>
            <tr>
                <td>Qt.ToolButtonTextBesideIcon</td>
                <td>The text appears beside the icon.</td>
            </tr>
            <tr>
                <td>Qt.ToolButtonTextUnderIcon</td>
                <td>The text appears under the icon.</td>
            </tr>
        </table>
    */
    property int toolButtonStyle: Qt.ToolButtonIconOnly
    
    background: "image://theme/toolbar_button_normal"
    backgroundChecked: "image://theme/toolbar_button_selected"
    backgroundDisabled: "image://theme/toolbar_button_disabled"
    backgroundPressed: "image://theme/toolbar_button_pressed"
    
    backgroundMarginLeft: 20
    backgroundMarginRight: 20
    
    buttonWidth: 70
}
