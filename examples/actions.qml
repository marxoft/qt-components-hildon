import QtQuick 1.0
import org.hildon.components 1.0

//! [Action]
Window {
    id: window
    
    title: qsTr("Actions Example")
    visible: true
    menuBar: MenuBar {
        MenuItem {
            action: action1
        }
        
        MenuItem {
            action: action2
        }
    }
    
//! [ExclusiveGroup]
    ExclusiveGroup {
        id: group
    }
    
    Action {
        id: action1
        
        autoRepeat: false
        checkable: true
        exclusiveGroup: group
        shortcut: Qt.Key_A
        text: qsTr("Action One")
        onTriggered: console.log(qsTr("Action One triggered"))
    }
    
    Action {
        id: action2
        
        autoRepeat: false
        checkable: true
        exclusiveGroup: group
        shortcut: Qt.Key_B
        text: qsTr("Action Two")
        onTriggered: console.log(qsTr("Action Two triggered"))
    }
//! [ExclusiveGroup]
    
    MouseArea {
        anchors.fill: parent
        onClicked: menu.popup()
    }
    
    Column {
        anchors.centerIn: parent
        spacing: platformStyle.paddingMedium
    
        Button {
            action: action1
        }
        
        Button {
            action: action2
        }
    }
    
    Menu {
        id: menu
        
        MenuItem {
            action: action1
        }
        
        MenuItem {
            action: action2
        }
    }
}
//! [Action]
