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
    \class SliderStyle
    \brief Provides styling properties for a Slider.
    
    \ingroup components
    
    \sa Slider
*/
Style {
    // Background
    
    /*!
        \brief The url for the left background image.
    */
    property url leftBackground: "image://theme/SliderLeftside"
    
    /*!
        \brief The url for the left background image used when the Slider is disabled.
    */
    property url leftBackgroundDisabled: "image://theme/SliderLeftsideDisabled"
    
    /*!
        \brief The url for the left background image.
    */
    property url rightBackground: "image://theme/SliderRightside"
    
    /*!
        \brief The url for the right background image used when the Slider is disabled.
    */
    property url rightBackgroundDisabled: "image://theme/SliderRightsideDisabled"
    
    /*!
        \brief The right margin for the background image, in pixels.
    */
    property int backgroundMarginRight: 0
    
    /*!
        \brief The left margin for the background image, in pixels.
    */
    property int backgroundMarginLeft: 6
    
    /*!
        \brief The top margin for the background image, in pixels.
    */
    property int backgroundMarginTop: 25
    
    /*!
        \brief The bottom margin for the background image, in pixels.
    */
    property int backgroundMarginBottom: 25

    // Handle
    
    /*!
        \brief The url for the handle image.
    */
    property url handle: "image://theme/SliderThumb"
    
    /*!
        \brief The url for the handle image used when the Slider is disabled.
    */
    property url handleDisabled: "image://theme/SliderThumbDisabled"
}
