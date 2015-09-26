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
    \class BiDirectionalSliderStyle
    \brief Provides styling properties for BiDirectionalSlider
    
    \ingroup components
    
    The BiDirectionalSliderStyle component can be used to provide custom styling for a BiDirectionalSlider.
    
    \sa BiDirectionalSlider
*/
Style {
    // Background
    
    /*!
        \brief The url for the background image.
    */
    property url background: "image://theme/BiDirectionalSliderBackground"
    
    /*!
        \brief The url for the background image used when the slider is disabled.
    */
    property url backgroundDisabled: "image://theme/BiDirectionalSliderBackgroundDisabled"
    
    /*!
        \brief The right margin for the background image, in pixels.
    */
    property int backgroundMarginRight: 10
    
    /*!
        \brief The left margin for the background image, in pixels.
    */
    property int backgroundMarginLeft: 10
    
    /*!
        \brief The top margin for the background image, in pixels.
    */
    property int backgroundMarginTop: 25
    
    /*!
        \brief The bottom margin for the background image, in pixels.
    */
    property int backgroundMarginBottom: 25
    
    // Center-point
    
    /*!
        \brief The url for the center-point image.
    */
    property url centerPoint: "image://theme/BiDirectionalSliderCenterPoint"
    
    /*!
        \brief The url for the center-point image used when the slider is disabled.
    */
    property url centerPointDisabled: "image://theme/BiDirectionalSliderCenterPointDisabled"
    
    // Handle
    
    /*!
        \brief The url for the handle image.
    */
    property url handle: "image://theme/SliderThumb"
    
    /*!
        \brief The url for the handle image used when the slider is disabled.
    */
    property url handleDisabled: "image://theme/SliderThumbDisabled"    
}
