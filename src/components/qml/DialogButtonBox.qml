/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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
    \class DialogButtonBox
    \brief Presents buttons in a layout that is appropriate for a dialog.
    
    \ingroup components
    
    \sa Button, Dialog, DialogButtonStyle
*/
Item {
    id: root
    
    /*!
        type:list<Button>
        \brief The list of buttons that have been added to the button box.
    */
    property alias buttons: grid.children
    
    /*!
        type:enumeration
        \brief The orientation of the button box.
        
        The orientation can be either Qt.Horizontal or Qt.Vertical (the default).
    */
    property int orientation: Qt.Vertical
    
    /*!
        type:flags
        \brief The standard buttons displayed in the button box.
        
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
    property int standardButtons: StandardButton.NoButton
    
    /*!
        \brief This signal is emitted when a button with role \c StandardButton.AcceptRole is clicked.
    */
    signal accepted
    
    /*!
        \brief This signal is emitted when \a button is clicked.
        @param type:Button button
    */
    signal clicked(variant button)
    
    /*!
        \brief This signal is emitted when a button with role \c StandardButton.HelpRole is clicked.
    */
    signal helpRequested
    
    /*!
        \brief This signal is emitted when a button with role \c StandardButton.RejectRole is clicked.
    */
    signal rejected    
    
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
        if ((role > StandardButton.InvalidRole) && (role <= StandardButton.ApplyRole)) {
            var button = buttonComponent.createObject(grid);
            button.text = text;
            button.role = role;
            return button;
        }
        
        return null;
    }
    
    /*!
        \brief Adds and returns a button using the standard type \a button.
        @param type:enumeration button
        @return type:Button
    */
    function addStandardButton(standardButton) {
        var role = StandardButton.InvalidRole;
        var text = "";
        
        switch (standardButton) {
        case StandardButton.Ok: {
            role = StandardButton.AcceptRole;
            text = qsTr("Done");
            break;
        }
        case StandardButton.Open: {
            role = StandardButton.AcceptRole;
            text = qsTr("Open");
            break;
        }
        case StandardButton.Save: {
            role = StandardButton.AcceptRole;
            text = qsTr("Save");
            break;
        }
        case StandardButton.Cancel: {
            role = StandardButton.RejectRole;
            text = qsTr("Cancel");
            break;
        }
        case StandardButton.Close: {
            role = StandardButton.RejectRole;
            text = qsTr("Close");
            break;
        }
        case StandardButton.Discard: {
            role = StandardButton.DestructiveRole;
            text = qsTr("Discard");
            break;
        }
        case StandardButton.Apply: {
            role = StandardButton.ApplyRole;
            text = qsTr("Apply");
            break;
        }
        case StandardButton.Reset: {
            role = StandardButton.ResetRole;
            text = qsTr("Reset");
            break;
        }
        case StandardButton.RestoreDefaults: {
            role = StandardButton.ResetRole;
            text = qsTr("Restore Defaults");
            break;
        }
        case StandardButton.Help: {
            role = StandardButton.HelpRole;
            text = qsTr("Help");
            break;
        }
        case StandardButton.SaveAll: {
            role = StandardButton.AcceptRole;
            text = qsTr("Save All");
            break;
        }
        case StandardButton.Yes: {
            role = StandardButton.YesRole;
            text = qsTr("Yes");
            break;
        }
        case StandardButton.YesToAll: {
            role = StandardButton.YesRole;
            text = qsTr("Yes to All");
            break;
        }
        case StandardButton.No: {
            role = StandardButton.NoRole;
            text = qsTr("No");
            break;
        }
        case StandardButton.NoToAll: {
            role = StandardButton.NoRole;
            text = qsTr("No to All");
            break;
        }
        case StandardButton.Abort: {
            role = StandardButton.RejectRole;
            text = qsTr("Abort");
            break;
        }
        case StandardButton.Retry: {
            role = StandardButton.AcceptRole;
            text = qsTr("Retry");
            break;
        }
        case StandardButton.Ignore: {
            role = StandardButton.AcceptRole;
            text = qsTr("Ignore");
            break;
        }
        default:
            return null;
        }
        
        var button = buttonComponent.createObject(grid);
        button.standardButton = standardButton;
        button.role = role;
        button.text = text;
        return button;
    }
    
    /*!
        \brief Returns the Button corresponding to the standard button \a which, or null if the standard
        button does not exist.
        @param type:enumeration which
        @return type:Button
    */
    function button(which) {
        for (var i = 0; i < grid.children.length; i++) {
            if (grid.children[i].standardButton === which) {
                return grid.children[i];
            }
        }
        
        return null;
    }
    
    /*!
        \brief Returns the button role for the specified \a button, or StandardButton.InvalidRole if the button
        has not been added to the button box.
        @param type:Button button
        @return type:enumeration
    */
    function buttonRole(button) {
        for (var i = 0; i < grid.children.length; i++) {
            if (grid.children[i] == button) {
                return button.role;
            }
        }
        
        return StandardButton.InvalidRole;
    }
    
    /*!
        \brief Deletes all buttons from the button box.
    */
    function clear() {
        for (var i = grid.children.length - 1; i >= 0; i--) {
            grid.children[i].destroy();
        }
    }
    
    /*!
        \brief Removes \a button from the button box and sets its parent to \c null.
    */
    function removeButton(button) {
        for (var i = 0; i < grid.children.length; i++) {
            if (grid.children[i] == button) {
                button.parent = null;
                break;
            }
        }
    }
    
    /*!
        \brief Returns the standard button for the specified \a button, or StandardButton.NoButton if the button
        is not a standard button.
        @param type:Button button
        @return type:enumeration
    */
    function standardButton(button) {
        for (var i = 0; i < grid.children.length; i++) {
            if (grid.children[i] == button) {
                return button.standardButton;
            }
        }
        
        return StandardButton.NoButton;
    }
    
    width: 180
    height: grid.height
    anchors {
        right: parent ? parent.right : undefined
        bottom: parent ? parent.bottom : undefined
    }
    
    DialogButtonStyle {
        id: dialogButtonStyle

        buttonWidth: root.width
    }
    
    Grid {
        id: grid
                
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        columns: 1
        spacing: platformStyle.paddingSmall
    }

    StateGroup {
        id: group

        states: State {
            name: "Horizontal"
            when: root.orientation == Qt.Horizontal

            PropertyChanges {
                target: dialogButtonStyle
                buttonWidth: 180
            }

            PropertyChanges {
                target: grid
                columns: children.length
            }
        }
    }
    
    Component {
        id: buttonComponent
        
        Button {
            id: dialogButton
            
            property int standardButton: StandardButton.NoButton
            property int role: StandardButton.InvalidRole
            
            style: dialogButtonStyle
            visible: role != StandardButton.RejectRole
            onClicked: {
                root.clicked(dialogButton);
                
                switch (role) {
                case StandardButton.AcceptRole:
                case StandardButton.YesRole:
                    root.accepted();
                    break;
                case StandardButton.RejectRole:
                case StandardButton.NoRole:
                    root.rejected();
                    break;
                    case StandardButton.HelpRole:
                    root.helpRequested();
                    break;
                default:
                    break;
                }
            }
        }
    }
    
    onStandardButtonsChanged: {
        for (var i = grid.children.length - 1; i >= 0; i--) {
            if (grid.children[i].standardButton != StandardButton.NoButton) {
                grid.children[i].visible = false;
                grid.children[i].destroy();
            }
        }
        
        if (standardButtons & StandardButton.Ok) {
            addStandardButton(StandardButton.Ok);
        }
        
        if (standardButtons & StandardButton.Open) {
            addStandardButton(StandardButton.Open);
        }
        
        if (standardButtons & StandardButton.Save) {
            addStandardButton(StandardButton.Save);
        }
                
        if (standardButtons & StandardButton.Cancel) {
            addStandardButton(StandardButton.Cancel);
        }
        
        if (standardButtons & StandardButton.Close) {
            addStandardButton(StandardButton.Close);
        }
                
        if (standardButtons & StandardButton.Discard) {
            addStandardButton(StandardButton.Discard);
        }
        
        if (standardButtons & StandardButton.Apply) {
            addStandardButton(StandardButton.Apply);
        }
        
        if (standardButtons & StandardButton.Reset) {
            addStandardButton(StandardButton.Reset);
        }
        
        if (standardButtons & StandardButton.RestoreDefaults) {
            addStandardButton(StandardButton.RestoreDefaults);
        }
        
        if (standardButtons & StandardButton.Help) {
            addStandardButton(StandardButton.Help);
        }
        
        if (standardButtons & StandardButton.SaveAll) {
            addStandardButton(StandardButton.SaveAll);
        }
        
        if (standardButtons & StandardButton.Yes) {
            addStandardButton(StandardButton.Yes);
        }
        
        if (standardButtons & StandardButton.YesToAll) {
            addStandardButton(StandardButton.YesToAll);
        }
        
        if (standardButtons & StandardButton.No) {
            addStandardButton(StandardButton.No);
        }
        
        if (standardButtons & StandardButton.NoToAll) {
            addStandardButton(StandardButton.NoToAll);
        }
        
        if (standardButtons & StandardButton.Abort) {
            addStandardButton(StandardButton.Abort);
        }
        
        if (standardButtons & StandardButton.Retry) {
            addStandardButton(StandardButton.Retry);
        }
        
        if (standardButtons & StandardButton.Ignore) {
            addStandardButton(StandardButton.Ignore);
        }
    }
}
