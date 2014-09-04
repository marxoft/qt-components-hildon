/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */
 
 import org.hildon.components 1.0
 import org.hildon.tracker 1.0
 
 Page {
    id: root
    
    windowTitle: qsTr("Videos")
    
    ListView {
        id: view
        
        anchors.fill: parent
        horizontalScrollMode: ListView.ScrollPerItem
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        model: TrackerQueryModel {
            id: videoModel

            itemType: "Videos"
            properties: [ "File:Name", "Video:Duration", "Video:LastPlayedFrame", "Video:Title" ]
            sortProperties: [ "Video:Title" ]
            onStatusChanged: root.showProgressIndicator = (status == 1)
        }
        delegate: VideoListDelegate {}
        onActivated: {
            loader.sourceComponent = dialog;
            loader.item.uri = videoModel.property(QModelIndex.row(currentIndex), "File:Uri");
            loader.item.open();
            loader.item.reload();
        }
    }
    
    Loader {
        id: loader
    }
    
    Component {
        id: dialog
        
        VideoDetailsDialog {}
    }
    
    Component.onCompleted: videoModel.reload()
}
