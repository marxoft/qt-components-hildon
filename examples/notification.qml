import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.desktop 1.0

Window {
    id: window
        
    title: qsTr("Notification Example")
    visible: true
        
    Button {
        id: button
        
        anchors.centerIn: parent
        width: 300
        text: qsTr("Show notification")
        onClicked: notificationComponent.createObject(window)
    }
    
    Component {
        id: notificationComponent
        
        Notification {
            id: notification
                
            category: "qt-components-hildon"
            hints: {"led-pattern": "PatternCommonNotification"}
            iconSource: "general_web"
            text: qsTr("This is an example QML notification")
            timeout: Notification.DefaultTimeout
            title: qsTr("QML notification")
            visible: true
            onAccepted: console.log(qsTr("Notification accepted"))
            onRejected: console.log(qsTr("Notification rejected"))
        }
    }
}
