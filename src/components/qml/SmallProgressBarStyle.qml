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
    \class SmallProgressBarStyle
    \brief Provides styling properties for a small ProgressBar.
    
    \ingroup components
    
    \sa ProgressBar
*/
ProgressBarStyle {
    background: "image://theme/ProgressbarSmallBackground"
    backgroundMarginLeft: 2
    backgroundMarginRight: 2
    backgroundMarginTop: 2
    backgroundMarginBottom: 2
    
    bar: "image://theme/ProgressbarSmall"
    barMarginLeft: 2
    barMarginRight: 2
    barMarginTop: 2
    barMarginBottom: 2
    barPaddingLeft: 3
    barPaddingRight: 3
    barPaddingTop: 3
    barPaddingBottom: 3
    
    progressBarHeight: 16
}
