import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("RadioButton Example")
    visible: true
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
//![RadioButtonStyle]      
        RadioButton {
            width: parent.width
            text: qsTr("Hildon RadioButton")
        }
//![RadioButtonStyle]

//![OssoRadioButtonStyle]
        RadioButton {
            width: parent.width
            style: OssoRadioButtonStyle {}
            text: qsTr("Osso RadioButton")
        }
//![OssoRadioButtonStyle]
    }
}
