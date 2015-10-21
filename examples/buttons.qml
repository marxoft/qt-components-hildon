import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window
    
    title: qsTr("Buttons Example")
    visible: true
    
    Flickable {
        id: flickable
        
        anchors.fill: parent
        contentHeight: column.height + platformStyle.paddingMedium
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    
        Column {
            id: column
        
            anchors {
                top: parent.top
                topMargin: platformStyle.paddingMedium
                horizontalCenter: parent.horizontalCenter
            }
            width: 300
            spacing: platformStyle.paddingMedium
        
//![Button]      
            Button {
                width: parent.width
                text: qsTr("Push Button")
                onClicked: console.log(qsTr("Button clicked"))
            }
//![Button]

//![AcceptButtonStyle]
            Button {
                width: parent.width
                style: AcceptButtonStyle {}
                text: qsTr("Accept Button")
            }
//![AcceptButtonStyle]

//![DialogButtonStyle]
            Button {
                width: parent.width
                style: DialogButtonStyle {}
                text: qsTr("Dialog Button")
            }
//![DialogButtonStyle]

//![RejectButtonStyle]
            Button {
                width: parent.width
                style: RejectButtonStyle {}
                text: qsTr("Reject Button")
            }
//![RejectButtonStyle]

//![ThumbButtonStyle]
            Button {
                width: parent.width
                style: ThumbButtonStyle {}
                text: qsTr("Thumb Button")
            }
//![ThumbButtonStyle]
        }
    }
}
