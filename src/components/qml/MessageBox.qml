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
import org.hildon.components 1.0

/*!
    \class MessageBox
    \brief Provides a modal dialog for informing the user or for asking the user a question and receiving an answer.
    
    \ingroup components
*/
Dialog {
    id: root
    
    /*!
        type:list<Button>
        \brief The list of buttons that have been added to the message box.
    */
    property alias buttons: buttonBox.buttons
    
    /*!
        \brief The button that was clicked by the user.
    */
    property Button clickedButton
    
    /*!
        type:flags
        \brief The standard buttons displayed in the message box.
        
        The standard buttons can be a bitwise OR combination of the following:
        
        <table>
        <tr>
        <th>Value</th>
        <th>Description</th>
        </tr>
        <tr>
        <td>StandardButton.Ok</td>
        <td>A 'Done' button defined with the StandardButton.AcceptRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Open</td>
        <td>A 'Open' button defined with the StandardButton.AcceptRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Save</td>
        <td>A 'Save' button defined with the StandardButton.AcceptRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Cancel</td>
        <td>A 'Cancel' button defined with the StandardButton.RejectRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Discard</td>
        <td>A 'Discard' button defined with the StandardButton.DescructiveRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Apply</td>
        <td>An 'Apply' button defined with the StandardButton.ApplyRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Reset</td>
        <td>A 'Reset' button defined with the StandardButton.ResetRole.</td>
        </tr>
        <tr>
        <td>StandardButton.RestoreDefaults</td>
        <td>A 'Restore Defaults' button defined with the StandardButton.ResetRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Help</td>
        <td>A 'Help' button defined with the StandardButton.HelpRole.</td>
        </tr>
        <tr>
        <td>StandardButton.SaveAll</td>
        <td>A 'Save All' button defined with the StandardButton.AcceptRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Yes</td>
        <td>A 'Yes' button defined with the StandardButton.YesRole.</td>
        </tr>
        <tr>
        <td>StandardButton.YesToAll</td>
        <td>A 'Yes to All' button defined with the StandardButton.YesRole.</td>
        </tr>
        <tr>
        <td>StandardButton.No</td>
        <td>A 'No' button defined with the StandardButton.NoRole.</td>
        </tr>
        <tr>
        <td>StandardButton.NoToAll</td>
        <td>A 'No to All' button defined with the StandardButton.NoRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Abort</td>
        <td>An 'Abort' button defined with the StandardButton.RejectRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Retry</td>
        <td>A 'Retry' button defined with the StandardButton.AcceptRole.</td>
        </tr>
        <tr>
        <td>StandardButton.Ignore</td>
        <td>An 'Ignore' button defined with the StandardButton.AcceptRole.</td>
        </tr>
        <tr>
        <td>StandardButton.NoButton</td>
        <td>An invalid button.</td>
        </tr>
        </table>
    */
    property alias standardButtons: buttonBox.standardButtons
    
    /*!
        type:string
        \brief The text to be displayed in the message label.        
    */
    property alias text: label.text
    
    /*!
        type:enumeration
        \brief The formatting to be used for message label.
    */
    property alias textFormat: label.textFormat
    
    /*!
        \brief This signal is emitted when \a button is clicked.
        @param type:Button button
    */
    signal buttonClicked(variant button)
    
    /*!
        \brief Displays a simple about box with the specified \a title and \a text.
        @param type:string title
        @param type:string text
    */
    function about(title, text) {
        root.title = title;
        root.text = text;
        root.standardButtons = StandardButton.Ok;
        root.exec();
    }
    
    /*!
        \brief Adds and returns a button with the given \a text and \a role.
        @param type:string text
        @param type:enumeration role
        @return type:Button
        
        The button role can be one of the following:
        
        <table>
        <tr>
        <th>Value</th>
        <th>Description</th>
        </tr>
        <tr>
        <td>StandardButton.AcceptRole</td>
        <td>Clicking the button causes the dialog to be accepted.</td>
        </tr>
        <tr>
        <td>StandardButton.RejectRole</td>
        <td>Clicking the button causes the dialog to be rejected.</td>
        </tr>
        <tr>
        <td>StandardButton.DestructiveRole</td>
        <td>Clicking the button causes a destructive change.</td>
        </tr>
        <tr>
        <td>StandardButton.ActionRole</td>
        <td>Clicking the button causes changes to the elements within the dialog.</td>
        </tr>
        <tr>
        <td>StandardButton.HelpRole</td>
        <td>Clicking the button requests help.</td>
        </tr>
        <tr>
        <td>StandardButton.YesRole</td>
        <td>The button is a 'Yes'-like button.</td>
        </tr>
        <tr>
        <td>StandardButton.NoRole</td>
        <td>The button is a 'No'-like button.</td>
        </tr>
        <tr>
        <td>StandardButton.ApplyRole</td>
        <td>Clicking the button applies content changes.</td>
        </tr>
        <tr>
        <td>StandardButton.ResetRole</td>
        <td>Clicking the button resets the dialog's fields to default values.</td>
        </tr>
        </table>
    */
    function addButton(text, role) {
        return buttonBox.addButton(text, role);
    }
    
    /*!
        \brief Adds and returns a button using the standard type \a button.
        @param type:enumeration button
        @return type:Button
    */
    function addStandardButton(standardButton) {
        return buttonBox.addStandardButton(standardButton);
    }
    
    /*!
        \brief Returns the Button corresponding to the standard button \a which, or null if the standard
        button does not exist.
        @param type:enumeration which
        @return type:Button
    */
    function button(which) {
        return buttonBox.button(which);
    }
    
    /*!
        \brief Returns the button role for the specified \a button, or StandardButton.InvalidRole if the button
        has not been added to the message box.
        @param type:Button button
        @return type:enumeration
    */
    function buttonRole(button) {
        return buttonBox.buttonRole(button);
    }
    
    /*!
        \brief Displays a critical message box with the specified \a title and \a text.
        @param type:string title
        @param type:string text
        @param type:flags buttons
        @return type:int
    */
    function critical(title, text, buttons) {
        root.title = title;
        root.text = text;
        root.standardButtons = (buttons == undefined ? StandardButton.Ok : buttons);
        root.exec();
        
        if (root.clickedButton) {
            return root.clickedButton.standardButton;
        }
        
        return StandardButton.NoButton;
    }
    
    /*!
        \brief Displays an informational message box with the specified \a title and \a text.
        @param type:string title
        @param type:string text
        @param type:flags buttons
        @return type:int
    */
    function information(title, text, buttons) {
        root.title = title;
        root.text = text;
        root.standardButtons = (buttons == undefined ? StandardButton.Ok : buttons);
        root.exec();
        
        if (root.clickedButton) {
            return root.clickedButton.standardButton;
        }
        
        return StandardButton.NoButton;
    }
    
    /*!
        \brief Displays a question message box with the specified \a title and \a text.
        @param type:string title
        @param type:string text
        @param type:flags buttons
        @return type:int
    */
    function question(title, text, buttons) {
        root.title = title;
        root.text = text;
        root.standardButtons = (buttons == undefined ? StandardButton.Yes | StandardButton.No : buttons);
        root.exec();
        
        if (root.clickedButton) {
            return root.clickedButton.standardButton;
        }
        
        return StandardButton.NoButton;
    }
    
    /*!
        \brief Removes \a button from the message box and sets its parent to \c null.
    */
    function removeButton(button) {
        buttonBox.removeButton(button);
    }
    
    /*!
        \brief Returns the standard button for the specified \a button, or StandardButton.NoButton if the button
        is not a standard button.
        @param type:Button button
        @return type:enumeration
    */
    function standardButton(button) {
        return buttonBox.standardButton(button);
    }
    
    /*!
        \brief Displays an warning message box with the specified \a title and \a text.
        @param type:string title
        @param type:string text
        @param type:flags buttons
        @return type:int
    */
    function warning(title, text, buttons) {
        root.title = title;
        root.text = text;
        root.standardButtons = (buttons == undefined ? StandardButton.Ok : buttons);
        root.exec();
        
        if (root.clickedButton) {
            return root.clickedButton.standardButton;
        }
        
        return StandardButton.NoButton;
    }
    
    title: " " // Prevent display of application name
    height: Math.max(label.height, buttonBox.height) + platformStyle.paddingMedium
    
    Label {
        id: label
        
        anchors {
            left: parent.left
            right: buttonBox.left
            rightMargin: platformStyle.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
    }
    
    DialogButtonBox {
        id: buttonBox
        
        standardButtons: StandardButton.Yes | StandardButton.No
        onAccepted: root.accept()
        onRejected: root.reject()
        onClicked: {
            root.clickedButton = button;
            root.buttonClicked(button);
        }
    }

    StateGroup {
        id: group

        states: State {
            name: "Portrait"
            when: screen.currentOrientation == Qt.WA_Maemo5PortraitOrientation

            AnchorChanges {
                target: label
                anchors {
                    right: parent.right
                    top: parent.top
                    verticalCenter: undefined
                }
            }

            PropertyChanges {
                target: label
                anchors.rightMargin: 0
            }

            PropertyChanges {
                target: buttonBox
                width: parent.width
            }

            PropertyChanges {
                target: root
                height: label.height + buttonBox.height + platformStyle.paddingMedium * 2
            }
        }
    }
}
