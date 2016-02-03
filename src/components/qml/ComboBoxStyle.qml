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
    \class ComboBoxStyle
    \brief Provides styling properties for a ComboBox.
    
    \ingroup components
    
    \sa ComboBox, OssoComboBoxStyle
*/
Style {
    /*!
        \brief The url for the background image.
    */
    property url background: "image://theme/ComboBoxTextInputLFrame"
    
    /*!
        \brief The url for the background image used when the ComboBox is disabled.
    */
    property url backgroundDisabled: "image://theme/ComboBoxTextInputLFrameDisabled"
    
    /*!
        \brief The url for the background image used when the ComboBox is selected.
    */
    property url backgroundSelected: "image://theme/ComboBoxTextInputLFrameFocused"
    
    /*!
        \brief The url for the button image.
    */
    property url button: "image://theme/ComboBoxTextInputRFrame"
    
    /*!
        \brief The url for the button image used when the ComboBox is disabled.
    */
    property url buttonDisabled: "image://theme/ComboBoxTextInputRFrameDisabled"
    
    /*!
        \brief The url for the button image used when the ComboBox is selected.
    */
    property url buttonSelected: "image://theme/ComboBoxTextInputRFrameFocused"
    
    /*!
        \brief The url for the background image used when the ComboBox is editable.
    */
    property url textInputBackground: "image://theme/ComboBoxTextInputLFrame"
    
    /*!
        \brief The url for the background image used when the ComboBox is editable and disabled.
    */
    property url textInputBackgroundDisabled: "image://theme/ComboBoxTextInputLFrameDisabled"
    
    /*!
        \brief The url for the background image used when the ComboBox is editable and selected.
    */
    property url textInputBackgroundSelected: "image://theme/ComboBoxTextInputLFrameFocused"
    
    /*!
        \brief The url for the button image used when the ComboBox is editable.
    */
    property url textInputButton: "image://theme/ComboBoxTextInputRFrame"
    
    /*!
        \brief The url for the button image used when the ComboBox is editable and disabled.
    */
    property url textInputButtonDisabled: "image://theme/ComboBoxTextInputRFrameDisabled"
    
    /*!
        \brief The url for the button image used when the ComboBox is editable and selected.
    */
    property url textInputButtonSelected: "image://theme/ComboBoxTextInputRFrameFocused"
    
    /*!
        \brief The right margin for the background image, in pixels.
    */
    property int backgroundMarginRight: 18
    
    /*!
        \brief The left margin for the background image, in pixels.
    */
    property int backgroundMarginLeft: 18
    
    /*!
        \brief The top margin for the background image, in pixels.
    */
    property int backgroundMarginTop: 22
    
    /*!
        \brief The bottom margin for the background image, in pixels.
    */
    property int backgroundMarginBottom: 22
    
    /*!
        \brief The url for the button icon.
    */
    property url icon: "image://theme/ComboBoxButtonNormal"
    
    /*!
        \brief The url for the button icon used when the ComboBox is disabled.
    */
    property url iconDisabled: "image://theme/ComboBoxButtonDisabled"
    
    /*!
        \brief The url for the button icon used when the ComboBox button is pressed.
    */
    property url iconPressed: "image://theme/ComboBoxButtonPressed"
    
    /*!
        \brief The url for the button icon used when the ComboBox is editable.
    */
    property url textInputIcon: "image://theme/ComboBoxButtonNormal"
    
    /*!
        \brief The url for the button icon used when the ComboBox is editable and disabled.
    */
    property url textInputIconDisabled: "image://theme/ComboBoxButtonDisabled"
    
    /*!
        \brief The url for the button icon used when the ComboBox is editable and the button is pressed.
    */
    property url textInputIconPressed: "image://theme/ComboBoxButtonPressed"
    
    /*!
        \brief The color of the text in the ComboBox.
    */
    property color textColor: platformStyle.reversedTextColor
        
    /*!
        \brief The left padding of the text, in pixels.
    */
    property int paddingLeft: platformStyle.paddingLarge
    
    /*!
        \brief The right padding of the text, in pixels.
    */
    property int paddingRight: platformStyle.paddingLarge
    
    /*!
        \brief The vertical offset of the text, in pixels.
    */
    property int baselineOffset: 2
    
    /*!
        \brief The width of the ComboBox button, in pixels.
    */
    property int buttonWidth: 60
    
    /*!
        \brief The default width of the ComboBox, in pixels.
    */
    property int defaultWidth: 250
    
    /*!
        \brief The default height of the ComboBox, in pixels.
    */
    property int defaultHeight: 70
    
    /*!
        type:ListViewStyle
        \brief The style used for the popup list view.
    */
    property QtObject listViewStyle: ListViewStyle {}
    
    /*!
        type:ListItemStyle
        \brief The style used for items in the popup list view.
    */
    property QtObject listItemStyle: ListItemStyle {}
}