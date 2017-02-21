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

Dialog {
    id: root
    
    /*!
        \brief Whether the combo box is editable.
        
        The default is \c true.
    */
    property bool comboBoxEditable: true
    
    /*!
        type:list
        \brief The list of items used in the combo box.
    */
    property variant comboBoxItems
    
    /*!
        \brief The precision of the double spinbox in decimals.
        
        The default is \c 1.
    */
    property int doubleDecimals: 1
    
    /*!
        \brief The maximum value of the double spinbox.
        
        The default is \c 2147483647.0.
    */
    property real doubleMaximum: 2147483647.0
    
    /*!
        \brief The minimum value of the double spinbox.
        
        The defaul is \c -2147483647.0.
    */
    property real doubleMinimum: -2147483647.0
    
    /*!
        \brief The current value of the double spinbox.
        
        The default is \c 0.0
    */
    property real doubleValue: 0.0
    
    /*!
        \brief The mode used for input.
        
        This property helps to determine which item is used for entering input.
        
        The possible values are:
        
        <table>
        <tr>
        <th>Value</th>
        <th>Description</th>
        </tr>
        <tr>
        <td>InputMode.TextInput</td>
        <td>Used to input text strings (default).</td>
        </tr>
        <tr>
        <td>InputMode.MultiLineTextInput</td>
        <td>Used to input multiline text strings.</td>
        </tr>
        <tr>
        <td>InputMode.IntInput</td>
        <td>Used to input integers.</td>
        </tr>
        <tr>
        <td>InputMode.DoubleInput</td>
        <td>Used to input floating point numbers with double precision accuracy.</td>
        </tr>
        <tr>
        <td>InputMode.ItemSelectInput</td>
        <td>Used to select an item from a list.</td>
        </tr>
        </table>
    */
    property int inputMode: InputMode.TextInput
    
    /*!
        \brief The maximum integer value accepted as input.
        
        The default is \c 2147483647.
    */
    property int intMaximum: 2147483647
    
    /*!
        \brief The minimum integer value accepted as input.
        
        The default is \c -2147483647.
    */
    property int intMinimum: -2147483647
    
    /*!
        \brief The step by which the integer value is increased and decreased.
        
        The default is \c 1.
    */
    property int intStep: 1
    
    /*!
        \brief The current integer value.
        
        The default is \c 0.
    */
    property int intValue: 0
    
    /*!
        \brief The label's text describing what needs to be input.
    */
    property alias labelText: label.text
    
    /*!
        \brief The text for the button used to accept the input.
    */
    property alias okButtonText: okButton.text
    
    /*!
        \brief The echo mode for the text input field.
        
        The default is \c Text.Normal
    */
    property int textEchoMode: TextInput.Normal
    
    /*!
        \brief The current text value.
    */
    property string textValue
    
    /*!
        \brief Convenience function to get a floating point number from the user.
        @param type:string title
        @param type:string label
        @param type:real value
        @param type:real minimum
        @param type:real maximum
        @param type:int decimals
        @return type:real
    */
    function getDouble(title, label, value, minimum, maximum, decimals) {
        root.title = title;
        root.labelText = label;
        root.doubleMinimum = (minimum == undefined ? -2147483647 : minimum);
        root.doubleMaximum = (maximum == undefined ? 2147483647 : maximum);
        root.doubleValue = (value == undefined ? 0.0 : value);
        root.doubleDecimals = (decimals == undefined ? 1 : decimals);
        root.inputMode = InputMode.DoubleInput;
        root.exec();
        return root.doubleValue;
    }
    
    /*!
        \brief Convenience function to get an integer from the user.
        @param type:string title
        @param type:string label
        @param type:int value
        @param type:int minimum
        @param type:int maximum
        @param type:int step
        @return type:int
    */
    function getInt(title, label, value, minimum, maximum, step) {
        root.title = title;
        root.labelText = label;
        root.intMinimum = (minimum == undefined ? -2147483647 : minimum);
        root.intMaximum = (maximum == undefined ? 2147483647 : maximum);
        root.intValue = (value == undefined ? 0 : value);
        root.intStep = (step == undefined ? 1 : step);
        root.inputMode = InputMode.IntInput;
        root.exec();
        return root.intValue;
    }
    
    /*!
        \brief Convenience function to let the user select an item from a list.
        @param type:string title
        @param type:string label
        @param type:list items
        @param type:int current
        @param type:bool editable
        @return type:string
    */
    function getItem(title, label, items, current, editable) {
        root.title = title;
        root.labelText = label;
        root.comboBoxItems = items;
        root.comboBoxEditable = (editable == undefined ? true : false);
        root.inputMode = InputMode.ItemSelectInput;
        loader.item.currentIndex = (current == undefined ? 0 : current);
        root.exec();
        return root.textValue;
    }
    
    /*!
        \brief Convenience function to get a multiline string from the user.
        @param type:string title
        @param type:string label
        @param type:enumeration mode
        @param type:string text
        @return type:string
    */
    function getMultiLineText(title, label, text) {
        root.title = title;
        root.labelText = label;
        root.textValue = (text == undefined ? "" : text);
        root.inputMode = InputMode.MultiLineTextInput;
        root.exec();
        return root.textValue;
    }
    
    /*!
        \brief Convenience function to get a string from the user.
        @param type:string title
        @param type:string label
        @param type:string text
        @return type:string
    */
    function getText(title, label, mode, text) {
        root.title = title;
        root.labelText = label;
        root.textEchoMode = (mode == undefined ? TextInput.Normal : mode);
        root.textValue = (text == undefined ? "" : text);
        root.inputMode = InputMode.TextInput;
        root.exec();
        return root.textValue;
    }
    
    title: " " // Prevent display of application name
    height: column.height + platformStyle.paddingMedium
    
    Column {
        id: column
        
        anchors {
            left: parent.left
            right: okButton.visible ? okButton.left : parent.right
            rightMargin: okButton.visible ? platformStyle.paddingMedium : 0
            top: parent.top
        }
        spacing: platformStyle.paddingMedium
        
        Label {
            id: label
            
            width: parent.width
            visible: text != ""
        }
        
        Loader {
            id: loader
            
            property bool completed: false
            
            function loadComponent() {
                if (!completed) {
                    return;
                }
                
                switch (root.inputMode) {
                case InputMode.TextInput:
                    sourceComponent = textField;
                    break;
                case InputMode.MultiLineTextInput:
                    sourceComponent = textArea;
                    break;
                case InputMode.IntInput:
                    sourceComponent = intSpinBox;
                    break;
                case InputMode.DoubleInput:
                    sourceComponent = doubleSpinBox;
                    break;
                case InputMode.ItemSelectInput:
                    sourceComponent = comboBox;
                    break;
                default:
                    break;
                }
            }            
        }
    }
    
    Button {
        id: okButton
        
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        style: DialogButtonStyle {}
        text: qsTr("Done")
        visible: text != ""
        onClicked: root.accept()
    }
    
    Component {
        id: comboBox
        
        ComboBox {
            width: column.width
            editable: root.comboBoxEditable
            model: root.comboBoxItems
            onSelected: root.textValue = text
            Component.onCompleted: forceActiveFocus()
        }
    }
    
    Component {
        id: doubleSpinBox
        
        DoubleSpinBox {
            width: column.width
            minimum: root.doubleMinimum
            maximum: root.doubleMaximum
            decimals: root.doubleDecimals
            value: root.doubleValue
            onValueChanged: root.doubleValue = value
            onAccepted: root.accept()
            Component.onCompleted: forceActiveFocus()
        }
    }
    
    Component {
        id: intSpinBox
        
        SpinBox {
            width: column.width
            minimum: root.intMinimum
            maximum: root.intMaximum
            value: root.intValue
            onValueChanged: root.intValue = value
            onAccepted: root.accept()
            Component.onCompleted: forceActiveFocus()
        }
    }
    
    Component {
        id: textField
        
        TextField {
            width: column.width
            echoMode: root.textEchoMode
            text: root.textValue
            onTextChanged: root.textValue = text
            onAccepted: root.accept()
            Component.onCompleted: forceActiveFocus()
        }
    }
    
    Component {
        id: textArea
        
        TextArea {
            width: column.width
            text: root.textValue
            onTextChanged: root.textValue = text
            Component.onCompleted: forceActiveFocus()
        }
    }
    
    onInputModeChanged: loader.loadComponent()
    Component.onCompleted: {
        loader.completed = true;
        loader.loadComponent();
    }
}
