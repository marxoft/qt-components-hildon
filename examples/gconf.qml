import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.settings 1.0

Dialog {
    id: dialog
    
    title: qsTr("GConf Example")
    height: column.height + platformStyle.paddingMedium

//! [GConfItem]
    GConfItem {
        id: gconfText
        
        key: "/apps/QtComponentsHildon/SettingsExample/text"
    }
    
    GConfItem {
        id: gconfNumber
        
        key: "/apps/QtComponentsHildon/SettingsExample/number"
    }
//! [GConfItem]
    
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
            text: gconfText.value
        }
        
        ValueButton {
            id: numberButton
            
            width: parent.width
            text: qsTr("Number")
            pickSelector: ListPickSelector {
                id: numberSelector
                
                model: 10
                currentIndex: gconfNumber.value
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
        gconfText.value = textField.text;
        gconfNumber.value = numberSelector.currentIndex;
    }
    
    Component.onCompleted: open()
}
