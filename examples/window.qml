import QtQuick 1.0
import org.hildon.components 1.0

ApplicationWindow {
    id: window
    
    title: qsTr("Window Example")
    visible: true
    
    Button {
        id: button
        
        anchors.centerIn: parent
        text: "Push window"
        onClicked: windowStack.pushWindow(Qt.resolvedUrl("SecondWindow.qml"))
    }
}
