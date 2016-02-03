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
    \class ButtonRow
    \brief Provides a horizontal layout for Button.
    
    \ingroup components
    
    \sa Button, ExclusiveGroup
*/
Item {
    id: root
    
    default property alias buttons: row.data
    
    ButtonStyle {
        id: leftButtonStyle
        
        background: "image://theme/ButtonGroupHorizontalLeftNormal"
        backgroundChecked: "image://theme/ButtonGroupHorizontalLeftPressed"
        backgroundDisabled: "image://theme/ButtonGroupHorizontalLeftDisabled"
        backgroundPressed: "image://theme/ButtonGroupHorizontalLeftPressed"
        buttonWidth: row.buttonWidth
    }
    
    ButtonStyle {
        id: middleButtonStyle
        
        background: "image://theme/ButtonGroupHorizontalMiddleNormal"
        backgroundChecked: "image://theme/ButtonGroupHorizontalMiddlePressed"
        backgroundDisabled: "image://theme/ButtonGroupHorizontalMiddleDisabled"
        backgroundPressed: "image://theme/ButtonGroupHorizontalMiddlePressed"
        buttonWidth: row.buttonWidth
    }
    
    ButtonStyle {
        id: rightButtonStyle
        
        background: "image://theme/ButtonGroupHorizontalRightNormal"
        backgroundChecked: "image://theme/ButtonGroupHorizontalRightPressed"
        backgroundDisabled: "image://theme/ButtonGroupHorizontalRightDisabled"
        backgroundPressed: "image://theme/ButtonGroupHorizontalRightPressed"
        buttonWidth: row.buttonWidth
    }
    
    height: leftButtonStyle.buttonHeight
    
    Row {
        id: row
        
        property int buttonWidth: 150
        property bool complete: false
        
        function updateButtons() {
            var count = children.length;
            
            if (count == 0) {
                return;
            }
            
            buttonWidth = (width > 0 ? Math.floor(width / count) : 150);
            
            for (var i = 0; i < count; i++) {
                var button = children[i];
                
                if (button.hasOwnProperty("style")) {
                    switch (i) {
                    case 0:
                        button.style = leftButtonStyle;
                        break;
                    case count - 1:
                        button.style = rightButtonStyle;
                        break;
                    default:
                        button.style = middleButtonStyle;
                        break;
                    }
                }
            }
        }

        anchors.fill: parent
        onChildrenChanged: if (complete) updateButtons();
        onWidthChanged: if (complete) updateButtons();
    }
    
    Component.onCompleted: {
        row.complete = true;
        row.updateButtons();
    }
}
            