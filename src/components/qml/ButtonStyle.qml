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
    \class ButtonStyle
    \brief Provides styling properties for Button.
    
    \ingroup components
    
    The ButtonStyle component can be used to provide custom styling for a Button.
    
    \sa Button
*/
Style {
    // Background
    
    /*!
        \brief The url for the background image.
    */
    property url background: "image://theme/FingerButtonNormal"
    
    /*!
        \brief The url for the background image used when the button is checked.
    */
    property url backgroundChecked: "image://theme/FingerButtonPressed"
    
    /*!
        \brief The url for the background image used when the button is disabled.
    */
    property url backgroundDisabled: "image://theme/FingerButtonDisabled"
    
    /*!
        \brief The url for the background image used when the button is pressed.
    */
    property url backgroundPressed: "image://theme/FingerButtonPressed"
    
    /*!
        \brief The right margin for the background image, in pixels.
    */
    property int backgroundMarginRight: 25
    
    /*!
        \brief The left margin for the background image, in pixels.
    */
    property int backgroundMarginLeft: 25
    
    /*!
        \brief The top margin for the background image, in pixels.
    */
    property int backgroundMarginTop: 25
    
    /*!
        \brief The bottom margin for the background image, in pixels.
    */
    property int backgroundMarginBottom: 25
    
    // Dimensions
    
    /*!
        \brief The default width for the button.
    */
    property int buttonWidth: 150
    
    /*!
        \brief The default height for the button.
    */
    property int buttonHeight: 70
    
    // Icon
    
    /*!
        \brief The width of the icon displayed in the button.
    */
    property int iconWidth: platformStyle.iconSizeLarge
    
    /*!
        \brief The height of the icon displayed in the button.
    */
    property int iconHeight: platformStyle.iconSizeLarge
    
    /*!
        \brief The opacity of the icon displayed in the button.
    */
    property real iconOpacity: platformStyle.enabledOpacity
    
    /*!
        \brief The opacity of the icon displayed in the button when the button is disabled.
    */
    property real disabledIconOpacity: platformStyle.disabledOpacity
    
    // Padding
    
    /*!
        \brief The padding used for the left side of the button.
    */
    property int paddingLeft: platformStyle.paddingMedium
    
    /*!
        \brief The padding used for the right side of the button.
    */
    property int paddingRight: platformStyle.paddingMedium
    
    // Text
    
    /*!
        \brief The font size of the text displayed in the button.
    */
    property int fontPointSize: platformStyle.fontSizeMedium
    
    /*!
        \brief The font capitalization of the text displayed in the button.
    */
    property int fontCapitalization: Font.MixedCase
    
    /*!
        \brief The font weight of the text displayed in the button.
    */
    property int fontWeight: Font.Normal
    
    /*!
        \brief The color of the text displayed in the button.
    */
    property color textColor: platformStyle.buttonTextColor
    
    /*!
        \brief The color of the text displayed in the button when the button is pressed.
    */
    property color pressedTextColor: platformStyle.buttonTextPressedColor
    
    /*!
        \brief The color of the text displayed in the button when the button is disabled.
    */
    property color disabledTextColor: platformStyle.buttonTextDisabledColor
    
    /*!
        \brief The color of the text displayed in the button when the button is checked.
    */
    property color checkedTextColor: platformStyle.buttonTextPressedColor
}
