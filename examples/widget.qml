import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.desktop 1.0

HomescreenWidget {
    id: widget
    
    property Dialog settingsDialog
    
    width: Math.max(100, widgetLabel.width * 2)
    height: widgetLabel.height * 2
    settingsAvailable: true
    
    Rectangle {
        id: widgetBackground
        
        anchors {
            fill: parent
            margins: 1
        }
        color: "#000"
        radius: 25
        opacity: 0.5
        smooth: true
    }
    
    Label {
        id: widgetLabel
        
        anchors.centerIn: parent
        text: qsTr("Widget Example")
    }
    
    Component {
        id: dialogComponent
        
        Dialog {
            id: dialog
            
            title: qsTr("New text")
            height: column.height + platformStyle.paddingMedium
            
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
                    text: qsTr("Please enter a new text:")
                }
                
                TextField {
                    id: textField
                    
                    width: parent.width
                }
            }
            
            Button {
                id: button
                
                anchors {
                    right: parent.right
                    bottom: parent.bottom
                }
                style: DialogButtonStyle {}
                text: qsTr("Done")
                enabled: textField.text != ""
                onClicked: dialog.accept()
            }
            
            onAccepted: widgetLabel.text = textField.text
            onStatusChanged: {
                if (status == DialogStatus.Open) {
                    textField.text = widgetLabel.text;
                    textField.forceActiveFocus();
                }
            }
        }
    }
    
    onSettingsRequested: {
        if (!settingsDialog) {
            settingsDialog = dialogComponent.createObject(widget);
        }
        
        settingsDialog.open();
    }
}
