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

Style {
    // Background
    property url background: "image://theme/FingerButtonNormal"
    property url backgroundChecked: "image://theme/FingerButtonPressed"
    property url backgroundDisabled: "image://theme/FingerButtonDisabled"
    property url backgroundPressed: "image://theme/FingerButtonPressed"
    
    property int backgroundMarginRight: 25
    property int backgroundMarginLeft: 25
    property int backgroundMarginTop: 25
    property int backgroundMarginBottom: 25
    
    // Dimensions
    property int buttonWidth: 150
    property int buttonHeight: 70
    
    // Icon
    property int iconWidth: platformStyle.iconSizeLarge
    property int iconHeight: platformStyle.iconSizeLarge
    property real iconOpacity: platformStyle.enabledOpacity
    property real disabledIconOpacity: platformStyle.disabledOpacity
    
    // Padding
    property int paddingLeft: platformStyle.paddingMedium
    property int paddingRight: platformStyle.paddingMedium
    
    // Text
    property int fontPointSize: platformStyle.fontSizeMedium
    property int fontCapitalization: Font.MixedCase
    property int fontWeight: Font.Normal
    
    property color textColor: platformStyle.buttonTextColor
    property color pressedTextColor: platformStyle.buttonTextPressedColor
    property color disabledTextColor: platformStyle.buttonTextDisabledColor
    property color checkedTextColor: platformStyle.buttonTextPressedColor
}
