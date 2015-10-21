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
    \class OssoListItemStyle
    \brief Provides Osso styling properties for a ListItem.
    
    \ingroup components
    
    \sa ListItem
*/
ListItemStyle {
    background: "image://theme/qgn_plat_tree_view_even"
    backgroundPressed: "image://theme/qgn_plat_focus_selection"
    backgroundSelected: "image://theme/qgn_plat_focus_selection"
    
    backgroundMarginLeft: 2
    backgroundMarginRight: 2
    backgroundMarginTop: 2
    backgroundMarginBottom: 2
    
    itemHeight: 28
}
