import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.utils 1.0

Window {
    id: window
    
    title: qsTr("File Example")
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
            text: qsTr("File name")
        }
        
        TextField {
            id: fileNameField
            
            width: parent.width
        }
        
        Button {
            id: button
            
            width: parent.width
            text: qsTr("Read file")
            onClicked: edit.text = file.readAll()
        }
        
        Label {
            width: parent.width
            text: qsTr("Result")
        }
        
        TextArea {
            id: edit
            
            width: parent.width
            readOnly: true
        }
    }
    
    File {
        id: file
        
        fileName: fileNameField.text
        onError: console.log(errorString)
    }
}