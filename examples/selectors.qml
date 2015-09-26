import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("Selectors Example")
    visible: true
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
//! [ListPickSelector]
        ValueButton {
            width: parent.width
            text: qsTr("Select from list")
            pickSelector: ListPickSelector {        
                model: ListModel {
                    ListElement { name: "One"; value: 1 }
                    ListElement { name: "Two"; value: 2 }
                    ListElement { name: "Three"; value: 3 }
                    ListElement { name: "Four"; value: 4 }
                    ListElement { name: "Five"; value: 5 }
                }
                textRole: "name"
            }
        }
//! [ListPickSelector]

//! [DatePickSelector]
        ValueButton {
            width: parent.width
            text: qsTr("Select date")
            pickSelector: DatePickSelector {}
        }
//! [DatePickSelector]

//! [TimePickSelector]
        ValueButton {
            width: parent.width
            text: qsTr("Select time")
            pickSelector: TimePickSelector {}
        }
//! [TimePickSelector]

//! [AbstractPickSelector]
        ValueButton {
            width: parent.width
            text: qsTr("Select a value")
            pickSelector: AbstractPickSelector {
                id: selector
        
                height: column.height + platformStyle.paddingMedium
        
                Column {            
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                    spacing: platformStyle.paddingMedium
            
                    Repeater {
                        id: repeater
                
                        model: 3
                
                        Button {
                            width: parent.width
                            text: index + 1
                            onClicked: {
                                selector.selected(index + 1);
                                selector.accept();
                            }
                        }
                    }
                }
            }
        }
//! [AbstractPickSelector]
    }
}
