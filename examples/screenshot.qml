import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.utils 1.0

Window {
    id: window
    
    title: qsTr("ScreenShot Example")
    visible: true
    
    Column {
        id: column
        
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: platformStyle.paddingMedium
        }
        spacing: platformStyle.paddingMedium
        
        Label {
            width: parent.width
            text: qsTr("Delay")
        }
        
        SpinBox {
            id: spinbox
            
            width: parent.width
            minimum: 1
            maximum: 20
            value: 1
            suffix: " " + qsTr("secs")
        }
        
        ValueButton {
            id: pathButton
            
            width: parent.width
            text: qsTr("Output folder")
            valueText: fileDialog.folder
            onClicked: fileDialog.open()
        }
        
        Button {
            id: screenshotButton
            
            width: parent.width
            text: qsTr("Take screenshot")
            onClicked: timer.start()
        }
    }

    FileDialog {
        id: fileDialog
    }
    
    Timer {
        id: timer
        
        interval: spinbox.value * 1000
        onTriggered: screenshot.grab()
    }
    
    ScreenShot {
        id: screenshot
        
        fileName: fileDialog.folder + "/screenshot.png"
    }
}
        