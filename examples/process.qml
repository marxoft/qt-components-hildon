import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.utils 1.0

Window {
    id: window
    
    title: qsTr("Process Example")
    visible: true
    
    Process {
        id: process
        
        command: textField.text
    }
    
    Column {
        id: column
        
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: platformStyle.paddingMedium
        }
        spacing: platformStyle.paddingMedium
        
        Label {
            width: parent.width
            text: qsTr("Command")
        }
        
        TextField {
            id: textField
            
            width: parent.width
            focus: true
            onAccepted: process.start()
        }
        
        Button {
            id: button
            
            width: parent.width
            text: process.state == Process.Running ? qsTr("Stop") : qsTr("Start")
            enabled: (textField.text != "") || (process.state == Process.Running)
            onClicked: process.state == Process.Running ? process.abort() : process.start()
        }
        
        Label {
            width: parent.width
            text: qsTr("Result")
        }
        
        TextArea {
            id: textArea
            
            width: parent.width
            readOnly: true
            text: process.standardOutput
        }
    }
}
