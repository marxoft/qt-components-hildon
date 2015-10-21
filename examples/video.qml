import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.multimedia 1.0

Window {
    id: window
    
    title: qsTr("Video Example")
        
    Video {
        id: player
        
        width: 800
        height: 480
        onError: console.log(qsTr("Error") + ": " + errorString)
    }
    
    Action {
        id: openAction
        
        shortcut: "Ctrl+O"
        autoRepeat: false
        onTriggered: fileDialog.open()
    }
    
    Action {
        id: playAction
        
        shortcut: "Space"
        autoRepeat: false
        enabled: player.source != ""
        onTriggered: player.playing = !player.playing
    }
    
    FileDialog {
        id: fileDialog
        
        onAccepted: {
            player.source = filePath;
            player.play();
        }
    }
    
    Component.onCompleted: showFullScreen()
}
    