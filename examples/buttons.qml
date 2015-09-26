import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("Buttons Example")
    visible: true
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
        Button {
            width: parent.width
            text: qsTr("Button One")
            onClicked: console.log(qsTr("Button One clicked"))
        }
        
        Button {
            width: parent.width
            iconName: "general_add"
            text: qsTr("Button Two")
            onClicked: console.log(qsTr("Button Two clicked"))
        }
    }
}
