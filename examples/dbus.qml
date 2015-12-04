import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.dbus 1.0

Window {
    id: window
    
    title: qsTr("DBus Example")
    visible: true

//! [DBusConnections]
    DBusConnections {
        id: connections
        
        function doSomething(something) {
            console.log(something);
        }
        
        serviceName: "org.hildon.dbus"
        path: "/org/hildon/dbus"
        interfaceName: "org.hildon.dbus"
    }
//! [DBusConnections]
    
//! [DBusMessage]
    DBusMessage {
        id: message
        
        serviceName: "org.hildon.dbus"
        path: "/org/hildon/dbus"
        interfaceName: "org.hildon.dbus"
        methodName: "doSomething"
        arguments: ["something"]
        onStatusChanged: {
            switch (status) {
            case DBusMessage.Ready:
            case DBusMessage.Error:
                console.log(reply);
                break;
            default:
                break;
            }
        }
    }
//! [DBusMessage]
    
    Button {
        id: button
        
        anchors.centerIn: parent
        width: 300
        text: qsTr("Send DBus message")
        onClicked: message.send()
    }    
}
