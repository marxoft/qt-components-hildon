import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.settings 1.0

Dialog {
    id: dialog
    
    title: qsTr("Settings Example")
    height: column.height + platformStyle.paddingMedium

//! [Settings]
    Settings {
        id: settings
        
        property int number
        property string text
        
        fileName: "/home/user/.config/QtComponentsHildon/SettingsExample.conf"
    }
//! [Settings]
    
    Column {
        id: column
        
        anchors {
            left: parent.left
            right: button.left
            rightMargin: platformStyle.paddingMedium
            bottom: parent.bottom
        }
        spacing: platformStyle.paddingMedium
        
        Label {
            width: parent.width
            text: qsTr("Text")
        }
        
        TextField {
            id: textField
            
            width: parent.width
            text: settings.text
        }
        
        ValueButton {
            id: numberButton
            
            width: parent.width
            text: qsTr("Number")
            pickSelector: ListPickSelector {
                id: numberSelector
                
                model: 10
                currentIndex: settings.number
            }
        }
    }
    
    Button {
        id: button
        
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        text: qsTr("Done")
        style: DialogButtonStyle {}
        onClicked: dialog.accept()
    }
    
    onAccepted: {
        settings.text = textField.text;
        settings.number = numberSelector.currentIndex;
    }
    
    Component.onCompleted: open()
}
