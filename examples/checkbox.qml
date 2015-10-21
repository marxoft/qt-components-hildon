import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("CheckBox Example")
    visible: true
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
//![CheckBoxStyle]      
        CheckBox {
            width: parent.width
            text: qsTr("Hildon CheckBox")
        }
//![CheckBoxStyle]

//![OssoCheckBoxStyle]
        CheckBox {
            width: parent.width
            style: OssoCheckBoxStyle {}
            text: qsTr("Osso CheckBox")
        }
//![OssoCheckBoxStyle]
    }
}
