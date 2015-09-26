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
import org.hildon.components 1.0

/*!
    \class ValueButtonStyle
    \brief Provides custom styling properties for a ValueButton.
    
    \ingroup components
    
    \sa ValueButton
*/
ButtonStyle {
    /*!
        type:enumeration
        \brief Specifies the layout of the text and value text in the ValueButton.
        
        Possible values are:
        
        <table>
            <tr>
                <th>Value</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>ValueLayout.ValueBesideText</td>
                <td>The value text is displayed to the right of the text.</td>
            </tr>
            <tr>
                <td>ValueLayout.ValueUnderText</td>
                <td>The value text is displayed under the text, aligned to the left (default).</td>
            </tr>
            <tr>
                <td>ValueLayout.ValueUnderTextCentered</td>
                <td>The value text is displayed under the text, aligned to the center.</td>
            </tr>
        </table>
    </table>
    */
    property int valueLayout: ValueLayout.ValueUnderText
    
    /*!
        \brief The color of the value text.
    */
    property color valueTextColor: platformStyle.activeTextColor
}
