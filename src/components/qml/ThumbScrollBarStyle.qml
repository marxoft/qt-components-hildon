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
    \class ThumbScrollBarStyle
    \brief Provides styling properties for a thumb-size ScrollBar.
    
    \ingroup components
    
    \sa ScrollBar
*/
ScrollBarStyle {
    subButton: "image://theme/qgn_plat_scroll_thumbsize_vertical_up_arrow_normal"
    subButtonDisabled: "image://theme/qgn_plat_scroll_thumbsize_vertical_up_arrow_disabled"
    subButtonPressed: "image://theme/qgn_plat_scroll_thumbsize_vertical_up_arrow_pressed"
    
    addButton: "image://theme/qgn_plat_scroll_thumbsize_vertical_down_arrow_normal"
    addButtonDisabled: "image://theme/qgn_plat_scroll_thumbsize_vertical_down_arrow_disabled"
    addButtonPressed: "image://theme/qgn_plat_scroll_thumbsize_vertical_down_arrow_pressed"
    
    shaft: "image://theme/qgn_plat_scroll_thumbsize_vertical_shaft_normal"
    shaftDisabled: "image://theme/qgn_plat_scroll_thumbsize_vertical_shaft_disabled"
    
    handle: "image://theme/qgn_plat_scroll_thumbsize_vertical_thumb_normal"
    handleDisabled: "image://theme/qgn_plat_scroll_thumbsize_vertical_thumb_disabled"
    handlePressed: "image://theme/qgn_plat_scroll_thumbsize_vertical_thumb_pressed"
    
    scrollBarWidth: 64
}
