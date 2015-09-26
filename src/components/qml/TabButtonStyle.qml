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
    \class TabButtonStyle
    \brief Provides appropriate styling properties for Button when used in a TabView.
    
    \ingroup components
    
    \sa Button, TabView
*/
ButtonStyle {
    background: "image://theme/qgn_plat_notebook_tab_passive"
    backgroundChecked: "image://theme/qgn_plat_notebook_tab_active"
    backgroundDisabled: "image://theme/qgn_plat_notebook_tab_passive"
    backgroundPressed: "image://theme/qgn_plat_notebook_tab_active"
    
    backgroundMarginRight: 10
    backgroundMarginLeft: 10
    backgroundMarginTop: 15
    backgroundMarginBottom: 15
    
    buttonHeight: 35
    
    iconWidth: platformStyle.iconSizeSmall
    iconHeight: platformStyle.iconSizeSmall
}
