import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    visible: true
    title: qsTr("Menus Example")
//! [MenuBar]
    menuBar: MenuBar {
        filters: [
            MenuItem {
                checkable: true
                text: qsTr("Filter One")
                onTriggered: console.log(qsTr("Filter One selected"))
            },
            
            MenuItem {
                checkable: true
                text: qsTr("Filter Two")
                onTriggered: console.log(qsTr("Filter Two selected"))
            }
        ]
        
        MenuItem {
            text: qsTr("MenuItem One")
            onTriggered: console.log(qsTr("MenuItem One triggered"))
        }
        
        MenuItem {
            text: qsTr("MenuItem Two")
            onTriggered: console.log(qsTr("MenuItem Two triggered"))
        }

//! [MenuBar item]
        MenuItem {
            CheckBox {
                text: qsTr("Menu CheckBox")
            }
        }
//! [MenuBar item]
        
        MenuItem {
            Slider {}
        }
    }
//! [MenuBar]
    
    Label {
        anchors.centerIn: parent
        text: "Tap to show menu"
    }
    
    MouseArea {
        anchors.fill: parent
        onClicked: menu.popup()
    }

//! [Menu]
    Menu {
        id: menu
        
        MenuItem {
            text: qsTr("MenuItem One")
            onTriggered: console.log(qsTr("MenuItem One triggered"))
        }
        
        MenuItem {
            text: qsTr("MenuItem Two")
            onTriggered: console.log(qsTr("MenuItem Two triggered"))
        }
        
        Menu {
            title: qsTr("Submenu One")
            
            MenuItem {
                text: qsTr("MenuItem Three")
                onTriggered: console.log(qsTr("MenuItem Three triggered"))
            }
        }
    }
//! [Menu]
}
