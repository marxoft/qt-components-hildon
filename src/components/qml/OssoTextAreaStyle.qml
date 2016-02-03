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
    \class OssoTextAreaStyle
    \brief Provides Osso styling properties for a TextArea.
    
    \ingroup components
    
    \sa TextArea
*/
TextAreaStyle {
    background: "image://theme/qgn_plat_multi_line_input"
    backgroundDisabled: "image://theme/qgn_plat_multi_line_input_disabled"
    backgroundSelected: "image://theme/qgn_plat_multi_line_input"
    backgroundCornerMargin: 2
    paddingLeft: platformStyle.paddingSmall
    paddingRight: platformStyle.paddingSmall
    paddingTop: platformStyle.paddingSmall
    paddingBottom: platformStyle.paddingSmall
}
