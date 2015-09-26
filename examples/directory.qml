import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.utils 1.0

Window {
    id: window
    
    title: qsTr("Directory Example")
    visible: true
    
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
            text: qsTr("Directory")
        }
        
        TextField {
            id: dirField
            
            width: parent.width
            text: "/home/user/MyDocs/"
        }
        
        Button {
            id: button
            
            width: parent.width
            text: qsTr("List files")
            onClicked: edit.text = dir.entryList().join("\n")
        }
        
        Label {
            width: parent.width
            text: qsTr("Results")
        }
        
        TextArea {
            id: edit
            
            width: parent.width
            readOnly: true
        }
    }
    
    Directory {
        id: dir
        
        filter: Directory.Files
        path: dirField.text ? dirField.text : "/home/user/MyDocs/"
    }
}