import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("Tabs Example")
    visible: true
//! [MenuBar filters]
    menuBar: MenuBar {
        filters: [
            MenuItem {
                checkable: true
                checked: true
                text: "Tab One"
                onTriggered: tabView.currentIndex = 0
            },
            
            MenuItem {
                checkable: true
                text: "Tab Two"
                onTriggered: tabView.currentIndex = 1
            },
            
            MenuItem {
                checkable: true
                text: "Tab Three"
                onTriggered: tabView.currentIndex = 2
            }
        ]
    }
//! [MenuBar filters]
    
//! [TabView]
    TabView {
        id: tabView
        
        anchors {
            fill: parent
            margins: platformStyle.paddingMedium
        }
        
        Tab {
            id: tabOne
            
            title: qsTr("Tab One")
            
            Label {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Tab One")
            }
        }
        
        Tab {
            id: tabTwo
            
            title: qsTr("Tab Two")
            
            Label {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Tab Two")
            }
        }
        
        Tab {
            id: tabThree
            
            title: qsTr("Tab Three")
            
            Label {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Tab Three")
            }
        }
    }
//! [TabView]
}
