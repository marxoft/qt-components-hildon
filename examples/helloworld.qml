import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("Hello World Example")
    visible: true
    
    Label {
        anchors.centerIn: parent
        text: qsTr("Hello World!")
    }
}
