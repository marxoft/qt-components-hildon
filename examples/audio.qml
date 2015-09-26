import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.multimedia 1.0

Window {
    id: window
    
    title: qsTr("Audio Example")
    visible: true
    
    Audio {
        id: player
    }
    
    Column {
        id: column
        
        anchors.centerIn: parent
        width: 300
        spacing: platformStyle.paddingMedium
        
        Button {
            id: playButton
            
            width: parent.width
            text: player.playing ? qsTr("Pause") : qsTr("Play")
            shortcut: "Space"
            enabled: player.source != ""
            onClicked: player.playing = !player.playing
        }
        
        Button {
            id: fileButton
            
            width: parent.width
            text: qsTr("Open file")
            shortcut: "Ctrl+O"
            onClicked: fileDialog.open()
        }
    }
        
    FileDialog {
        id: fileDialog
        
        onAccepted: {
            player.source = filePath;
            player.play();
        }
    }
}       
