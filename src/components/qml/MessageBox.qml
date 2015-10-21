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
    \class MessageBox
    \brief Provides a modal dialog for informing the user or for asking the user a question and receiving an answer.
    
    \ingroup components
*/
Dialog {
    id: root
    
    /*!
        type:string
        \brief The text to be displayed in the 'accept' button.
        
        If the text is set to an empty string, the button will not be displayed.
    */
    property alias acceptButtonText: acceptButton.text
    
    /*!
        type:string
        \brief The text to be displayed in the 'reject' button.
        
        If the text is set to an empty string, the button will not be displayed.
    */
    property alias rejectButtonText: rejectButton.text
    
    /*!
        type:string
        \brief The text to be displayed in the message label.        
    */
    property alias text: label.text
    
    /*!
        \type:enumeration
        \brief The formatting to be used for message label.
    */
    property alias textFormat: label.textFormat
    
    /*!
        \brief Shows the message box as a modal dialog, blocking until the user closes it.
        @return type:enumeration
        
        The return value is the one of the following:
        
        <table>
            <tr>
                <th>Name</th>
                <th>Description</th>
            </tr>
            </tr>
                <td>Dialog.Accepted</td>
                <td>The dialog was accepted.</td>
            </tr>
            <tr>
                <td>Dialog.Rejected</td>
                <td>The dialog was rejected.</td>
            </tr>
        </table>
    */
    function open() {
        return exec();
    }
    
    title: " " // Prevent display of application name
    height: Math.max(label.height, buttonColumn.height) + platformStyle.paddingLarge
    
    Label {
        id: label
        
        anchors {
            left: parent.left
            right: buttonColumn.left
            rightMargin: platformStyle.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
    }
    
    Column {
        id: buttonColumn
        
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        spacing: platformStyle.paddingSmall
        
        Button {
            id: acceptButton
            
            style: DialogButtonStyle {}
            text: qsTr("Yes")
            visible: text != ""
            onClicked: root.accept();
        }
        
        Button {
            id: rejectButton
            
            style: DialogButtonStyle {}
            text: qsTr("No")
            visible: text != ""
            onClicked: root.reject()
        }
    }
}
