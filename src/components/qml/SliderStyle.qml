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
    // Background
    property url leftBackground: "image://theme/SliderLeftside"
    property url leftBackgroundDisabled: "image://theme/SliderLeftsideDisabled"
    property url rightBackground: "image://theme/SliderRightside"
    property url rightBackgroundDisabled: "image://theme/SliderRightsideDisabled"
    
    property int backgroundMarginRight: 0
    property int backgroundMarginLeft: 6
    property int backgroundMarginTop: 25
    property int backgroundMarginBottom: 25

    // Handle
    property url handle: "image://theme/SliderThumb"
    property url handleDisabled: "image://theme/SliderThumbDisabled"
}
