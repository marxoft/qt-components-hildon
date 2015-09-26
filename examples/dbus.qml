import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.dbus 1.0

Window {
    id: window
    
    title: qsTr("DBus Example")
    visible: true

//! [DBusAdaptor]
    DBusAdaptor {
        id: adaptor
        
        serviceName: "org.hildon.dbus.DBusExample"
        path: "/org/hildon/dbus"
        target: window
    }
//! [DBusAdaptor]
    
//! [DBusMessage]
    DBusMessage {
        id: message
        
        serviceName: "org.hildon.dbus.DBusExample"
        path: "/org/hildon/dbus"
        interfaceName: "org.hildon.dbus.DBusExample"
        methodName: "setWindowTitle"
        arguments: [ qsTr("New window title") ]
        onStatusChanged: {
            switch (status) {
            case DBusMessage.Ready:
                console.log(replyString);
                break;
            case DBusMessage.Error:
                console.log("Error");
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
