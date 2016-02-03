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
    \class ScrollBarStyle
    \brief Provides styling properties for a ScrollBar.
    
    \ingroup components
    
    \sa ScrollBar
*/
Style {
    // Sub button
    
    /*!
        \brief The url for the sub button.        
    */
    property url subButton: "image://theme/qgn_plat_scroll_vertical_up_arrow_normal"
    
    /*!
        \brief The url for the sub button when disabled.        
    */
    property url subButtonDisabled: "image://theme/qgn_plat_scroll_vertical_up_arrow_disabled"
    
    /*!
        \brief The url for the sub button when pressed.        
    */
    property url subButtonPressed: "image://theme/qgn_plat_scroll_vertical_up_arrow_pressed"
    
    // Add button
    
    /*!
        \brief The url for the add button.        
    */
    property url addButton: "image://theme/qgn_plat_scroll_vertical_down_arrow_normal"
    
    /*!
        \brief The url for the add button when disabled.        
    */
    property url addButtonDisabled: "image://theme/qgn_plat_scroll_vertical_down_arrow_disabled"
    
    /*!
        \brief The url for the add button when pressed.        
    */
    property url addButtonPressed: "image://theme/qgn_plat_scroll_vertical_down_arrow_pressed"
    
    // Shaft
    
    /*!
        \brief The url for the shaft.        
    */
    property url shaft: "image://theme/qgn_plat_scroll_horizontal_shaft_normal"
    
    /*!
        \brief The url for the shaft when disabled.        
    */
    property url shaftDisabled: "image://theme/qgn_plat_scroll_vertical_shaft_disabled"
    
    /*!
        \brief The right margin for the shaft image, in pixels.
    */
    property int shaftMarginRight: 0
    
    /*!
        \brief The left margin for the shaft image, in pixels.
    */
    property int shaftMarginLeft: 0
    
    /*!
        \brief The top margin for the shaft image, in pixels.
    */
    property int shaftMarginTop: 10
    
    /*!
        \brief The bottom margin for the shaft image, in pixels.
    */
    property int shaftMarginBottom: 10
    
    // Handle
    
    /*!
        \brief The url for the handle.        
    */
    property url handle: "image://theme/qgn_plat_scroll_horizontal_thumb_normal"
    
    /*!
        \brief The url for the handle when disabled.        
    */
    property url handleDisabled: "image://theme/qgn_plat_scroll_vertical_thumb_disabled"
    
    /*!
        \brief The url for the handle when pressed.        
    */
    property url handlePressed: "image://theme/qgn_plat_scroll_vertical_thumb_pressed"
    
    /*!
        \brief The right margin for the handle image, in pixels.
    */
    property int handleMarginRight: 0
    
    /*!
        \brief The left margin for the handle image, in pixels.
    */
    property int handleMarginLeft: 0
    
    /*!
        \brief The top margin for the handle image, in pixels.
    */
    property int handleMarginTop: 10
    
    /*!
        \brief The bottom margin for the handle image, in pixels.
    */
    property int handleMarginBottom: 10
    
    // Dimensions
    
    /*!
        \brief The width of the ScrollBar.
    */
    property int scrollBarWidth: 22
}
