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
    \class TextFieldStyle
    \brief Provides styling properties for a TextField.
    
    \ingroup components
    
    \sa TextField
*/
Style {
    // Colors
    
    /*!
        \brief The text color.
    */
    property color textColor: platformStyle.reversedTextColor
    
    /*!
        \brief The selected text color
    */
    property color selectedTextColor: platformStyle.reversedTextColor
    
    /*!
        \brief The selection background color.
    */
    property color selectionColor: platformStyle.selectionColor

    // Background
    
    /*!
        \brief The url for the background image.
    */
    property url background: "image://theme/TextInputFrame"
    
    /*!
        \brief The url for the background image used when the TextField is selected.
    */
    property url backgroundSelected: "image://theme/TextInputFrameFocused"
    
    /*!
        \brief The url for the background image used when the TextField is disabled.
    */
    property url backgroundDisabled: "image://theme/TextInputFrameDisabled"
    
    /*!
        \brief The margin for the background image, in pixels.
    */
    property int backgroundCornerMargin: 22
    
    // Padding
    
    /*!
        \brief The left padding of the text, in pixels.
    */
    property int paddingLeft: platformStyle.paddingLarge
    
    /*!
        \brief The right padding of the text, in pixels.
    */
    property int paddingRight: platformStyle.paddingLarge
    
    /*!
        \brief The vertical offset of the text, in pixels.
    */
    property int baselineOffset: 2
    
    /*!
        \brief The default width of the TextField, in pixels.
    */
    property int defaultWidth: 250
}
