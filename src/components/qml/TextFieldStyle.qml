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

Style {
    // Colors
    property color textColor: platformStyle.reversedTextColor
    property color selectedTextColor: platformStyle.reversedTextColor
    property color selectionColor: platformStyle.selectionColor

    // Background
    property url background: "image://theme/TextInputFrame"
    property url backgroundSelected: "image://theme/TextInputFrameFocused"
    property url backgroundDisabled: "image://theme/TextInputFrameDisabled"
    property int backgroundCornerMargin: 22
    
    // Padding
    property int paddingLeft: platformStyle.paddingLarge
    property int paddingRight: platformStyle.paddingLarge

    property int baselineOffset: 2
    property int defaultWidth: 250
}
