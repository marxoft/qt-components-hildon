import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("TextField Example")
    visible: true
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
//![TextFieldStyle]      
        TextField {
            width: parent.width
            text: qsTr("Hildon TextField")
        }
//![TextFieldStyle]

//![OssoTextFieldStyle]
        TextField {
            width: parent.width
            style: OssoTextFieldStyle {}
            text: qsTr("Osso TextField")
        }
//![OssoTextFieldStyle]
    }
}
