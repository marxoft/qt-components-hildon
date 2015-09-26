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
import org.hildon.components 1.0

/*!
    \class AbstractPickSelector
    \brief The base class for pick selectors.
    
    \ingroup components
    
    The AbstractPickSelector is used for creating custom pick selectors. Typically, a pick selector is assigned to a 
    ValueButton, but can also be used standalone.
    
    \snippet selectors.qml AbstractPickSelector
    
    \sa ValueButton
*/
Dialog {
    /*!
        \brief This property should be set to the display text of the current selected value.        
    */
    property string currentValueText
    
    /*!
        \brief This signal should be emitted when a value is selected.
        
        When the signal is emitted, \link currentValueText\endlink will be updated to \a text.
        
        \sa currentValueText
    */
    signal selected(string text)
    
    onSelected: currentValueText = text
}
