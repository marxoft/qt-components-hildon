import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.webkit 1.0

Window {
    id: window
    
    visible: true
    title: webView.title ? webView.title : qsTr("WebView Example")
    
    Flickable {
        id: flickable
        
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: toolBar.top
        }
        contentHeight: webView.height
        
        WebView {
            id: webView
            
            preferredWidth: flickable.width
        }
    }
    
    ToolBar {
        id: toolBar
        
        anchors.bottom: parent.bottom
        
        ToolButton {
            id: backButton
            
            shortcut: "Backspace"
            iconName: "general_back"
            onClicked: webView.back()
        }
        
        ToolButton {
            id: forwardButton
            
            shortcut: "Shift+Backspace"
            iconName: "general_forward"
            onClicked: webView.forward()
        }        
        
        TextField {
            id: urlField
            
            width: parent.width - 210
            onAccepted: if (text) webView.url = text;
        }
        
        ToolButton {
            id: loadButton
            
            shortcut: "Ctrl+R"
            iconName: webView.status == WebView.Loading ? "general_stop" : "general_refresh"
            onClicked: webView.status == WebView.Loading ? webView.stop() : webView.reload()
        }
    }
}
