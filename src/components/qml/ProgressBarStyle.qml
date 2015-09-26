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
    \class ProgressBarStyle
    \brief Provides styling properties for a ProgressBar.
    
    \ingroup components
    
    \sa ProgressBar
*/
Style {
    // Background
    
    /*!
        \brief The url for the background image.
    */
    property url background: "image://theme/ProgressbarBackground"
    
    /*!
        \brief The right margin of the background image, in pixels.
    */
    property int backgroundMarginRight: 25
    
    /*!
        \brief The left margin of the background image, in pixels.
    */
    property int backgroundMarginLeft: 25
    
    /*!
        \brief The top margin of the background image, in pixels.
    */
    property int backgroundMarginTop: 25
    
    /*!
        \brief The right margin of the background image, in pixels.
    */
    property int backgroundMarginBottom: 25
    
    // Bar
    
    /*!
        \brief The url for the bar image.
    */
    property url bar: "image://theme/Progressbar"
    
    /*!
        \brief The right margin of the bar image, in pixels.
    */
    property int barMarginRight: 10
    
    /*!
        \brief The left margin of the bar image, in pixels.
    */
    property int barMarginLeft: 10
    
    /*!
        \brief The top margin of the bar image, in pixels.
    */
    property int barMarginTop: 25
    
    /*!
        \brief The bottom margin of the bar image, in pixels.
    */
    property int barMarginBottom: 25
    
    /*!
        \brief The left padding of the bar image, in pixels.
    */
    property int barPaddingLeft: platformStyle.paddingSmall
    
    /*!
        \brief The right padding of the bar image, in pixels.
    */
    property int barPaddingRight: platformStyle.paddingSmall
    
    /*!
        \brief The top padding of the bar image, in pixels.
    */
    property int barPaddingTop: platformStyle.paddingSmall
    
    /*!
        \brief The left bottom of the bar image, in pixels.
    */
    property int barPaddingBottom: platformStyle.paddingSmall
}
