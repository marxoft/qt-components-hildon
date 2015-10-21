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
    \class TextAreaStyle
    \brief Provides styling properties for a TextArea.
    
    \ingroup components
    
    \sa TextArea, OssoTextAreaStyle
*/
TextFieldStyle {
    /*!
        \brief The top padding of the text, in pixels.
    */
    property int paddingTop: platformStyle.paddingLarge
    
    /*!
        \brief The bottom padding of the text, in pixels.
    */
    property int paddingBottom: platformStyle.paddingLarge
    
    /*!
        \brief The default height of the TextArea.
    */
    property int defaultHeight: 120
}
