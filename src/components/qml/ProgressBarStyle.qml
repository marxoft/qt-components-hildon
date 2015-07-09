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
    property url background: "image://theme/ProgressbarBackground"
    
    property int backgroundMarginRight: 25
    property int backgroundMarginLeft: 25
    property int backgroundMarginTop: 25
    property int backgroundMarginBottom: 25
    
    // Bar
    property url bar: "image://theme/Progressbar"
    
    property int barMarginRight: 10
    property int barMarginLeft: 10
    property int barMarginTop: 25
    property int barMarginBottom: 25
    
    property int barPaddingLeft: platformStyle.paddingSmall
    property int barPaddingRight: platformStyle.paddingSmall
    property int barPaddingTop: platformStyle.paddingSmall
    property int barPaddingBottom: platformStyle.paddingSmall
}
