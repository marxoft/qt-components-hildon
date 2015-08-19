/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.0
import org.hildon.components 1.0
import org.hildon.webkit 1.0

Window {
    id: window
    
    visible: true
    title: webView.title ? webView.title : qsTr("Webkit example")
    
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
            
            iconName: "general_back"
            onClicked: webView.back()
        }
        
        ToolButton {
            id: forwardButton
            
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
            
            iconName: webView.status == WebView.Loading ? "general_stop" : "general_refresh"
            onClicked: webView.status == WebView.Loading ? webView.stop() : webView.reload()
        }
    }
}
