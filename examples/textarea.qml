import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("TextArea Example")
    visible: true
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
//![TextAreaStyle]      
        TextArea {
            width: parent.width
            text: qsTr("Hildon TextArea")
        }
//![TextAreaStyle]

//![OssoTextAreaStyle]
        TextArea {
            width: parent.width
            style: OssoTextAreaStyle {}
            text: qsTr("Osso TextArea")
        }
//![OssoTextAreaStyle]
    }
}
