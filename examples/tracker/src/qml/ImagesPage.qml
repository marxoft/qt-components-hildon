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
    
    windowTitle: qsTr("Images")
    
    ListView {
        id: view
        
        anchors {
            fill: parent
            leftMargin: 30
        }
        viewMode: ListView.IconMode
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        model: TrackerQueryModel {
            id: imageModel

            itemType: "Images"
            properties: [ "File:Name", "Image:Date", "Image:Rating" ]
            sortProperties: [ "Image:Date", "File:Path", "File:Name" ]
            onStatusChanged: root.showProgressIndicator = (status == 1)
        }
        delegate: ImageListDelegate {}
        onActivated: {
            dialog.uri = imageModel.property(QModelIndex.row(currentIndex), "File:Uri");
            dialog.open();
            dialog.reload();
        }
    }
    
    ImageDetailsDialog {
        id: dialog
    }
    
    onVisibleChanged: if (visible) imageModel.reload();
}
