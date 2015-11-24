import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("Sort/Filter Example")
    visible: true
    
    ListView {
        id: view
        
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: toolbar.top
        }
//![SortFilterProxyModel]
        model: SortFilterProxyModel {
            id: filterModel
            
            sourceModel: ListModel {
                id: listModel
                
                ListElement {name: "One"; value: 1}
                ListElement {name: "Two"; value: 2}
                ListElement {name: "Three"; value: 3}
                ListElement {name: "Four"; value: 4}
                ListElement {name: "Five"; value: 5}
                ListElement {name: "Six"; value: 6}
                ListElement {name: "Seven"; value: 7}
                ListElement {name: "Eight"; value: 8}
                ListElement {name: "Nine"; value: 9}
                ListElement {name: "Ten"; value: 10}
            }
            dynamicSortFilter: true
            filterCaseSensitivity: Qt.CaseInsensitive
            filterFixedString: textField.text
            filterRole: "name"
            sortCaseSensitivity: Qt.CaseInsensitive
            sortRole: "value"
        }
//![SortFilterProxyModel]
        delegate: ListItem {
            Label {
                anchors.centerIn: parent
                text: "name: " + name + ", value: " + value
            }
        }
    }
    
    ToolBar {
        id: toolbar
        
        anchors.bottom: parent.bottom
        spacing: platformStyle.paddingMedium
        
        TextField {
            id: textField
            
            width: parent.width - parent.spacing * 2 - filterButton.width - sortButton.width
            placeholderText: qsTr("Filter string")
        }
        
        ValueButton {
            id: filterButton
            
            text: qsTr("Filter role")
            pickSelector: filterSelector
        }
        
        ValueButton {
            id: sortButton
            
            text: qsTr("Sort role")
            pickSelector: sortSelector
        }
    }
    
    ListPickSelector {
        id: filterSelector
        
        model: ["name", "value"]
        currentIndex: 0
        onSelected: filterModel.filterRole = currentValueText
    }
    
    ListPickSelector {
        id: sortSelector
        
        model: ["name", "value"]
        currentIndex: 1
        onSelected: {
            filterModel.sortRole = currentValueText;
            filterModel.sort();
        }
    }
}
