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
import "Utils.js" as Utils

Dialog {
    id: root

    property string uri

    function reload() {
        request.reload();
    }

    windowTitle: qsTr("Details")
    height: window.inPortrait ? 600 : 360
    content: Flickable {
        id: flicker

        anchors.fill: parent

        Column {
            id: column

            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }

            Label {
                font.pixelSize: platformStyle.fontSizeLarge
                text: qsTr("Metadata")
            }

            Row {
                
                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 200
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Title")
                }

                TextField {
                    id: titleField
                }
            }

            Row {
                
                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 200
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Artist")
                }

                TextField {
                    id: artistField
                }
            }

            Label {
                font.pixelSize: platformStyle.fontSizeLarge
                text: qsTr("General")
            }

            Row {
                visible: nameLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Name")
                }

                Label {
                    id: nameLabel
    
                    wordWrap: true
                }
            }

            Row {
                visible: typeLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Type")
                }

                Label {
                    id: typeLabel
                }
            }

            Row {
                visible: locationLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Location")
                }

                Image {
                    width: 32
                    height: 32
                    source: "file:///usr/share/icons/hicolor/32x32/hildon/general_folder.png"
                }

                Label {
                    id: locationLabel
                }
            }

            Row {
                visible: storageLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Storage")
                }

                Image {
                    source: "file:///usr/share/icons/hicolor/32x32/hildon/general_folder.png"
                }

                Label {
                    id: storageLabel
                }
            }

            Row {
                visible: dateLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Date")
                }

                Label {
                    id: dateLabel
                }
            }

            Row {
                visible: timeLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Time")
                }

                Label {
                    id: timeLabel
                }
            }

            Row {
                visible: sizeLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Size")
                }

                Label {
                    id: sizeLabel
                }
            }
            
            Row {
                visible: sizeLabel.text != ""

                Item {
                    width: platformStyle.paddingSmall
                }

                Label {
                    width: 250
                    color: platformStyle.secondaryTextColor
                    text: qsTr("Duration")
                }

                Label {
                    id: durationLabel
                }
            }
        }
    }

    buttons: Button {
        text: qsTr("Done")
        onClicked: root.accept()
    }

    TrackerItemRequest {
        id: request

        itemType: "Music"
        uri: root.uri
        properties: [
            "File:Mime",
            "File:Name",
            "File:Path",
            "File:Size",
            "Audio:Artist",
            "Audio:DateAdded",
            "Audio:Duration",
            "Audio:Title"
        ]
        onStatusChanged: {
            switch (status) {
            case 1:
                root.showProgressIndicator = true;
                break;
            case 2: {
                try {
                    titleField.text = metaData["Audio:Title"];
                }
                catch (e) {
                    titleField.clear();
                }

                try {
                    artistField.text = metaData["Audio:Artist"];
                }
                catch (e) {
                    artistField.clear();
                }

                try {
                    nameLabel.text = metaData["File:Name"].substring(0, metaData["File:Name"].lastIndexOf("."));
                }
                catch (e) {
                    nameLabel.clear();
                }

                try {
                    typeLabel.text = metaData["File:Mime"].substring(metaData["File:Mime"].lastIndexOf("/") + 1).toUpperCase() + " " + qsTr("audio");
                }
                catch (e) {
                    typeLabel.clear();
                }

                try {
                    locationLabel.text = metaData["File:Path"].substring(metaData["File:Path"].lastIndexOf("/") + 1);
                }
                catch (e) {
                    locationLabel.clear();
                }

                try {
                    dateLabel.text = Utils.dateStringFromSecs(metaData["Audio:DateAdded"]);
                }
                catch (e) {
                    dateLabel.clear();
                }

                try {
                    timeLabel.text = Utils.timeStringFromSecs(metaData["Audio:DateAdded"]);
                }
                catch (e) {
                    timeLabel.clear();
                }

                try {
                    sizeLabel.text = Utils.fileSizeFromBytes(parseInt(metaData["File:Size"]));
                }
                catch (e) {
                    sizeLabel.clear();
                }

                try {
                    durationLabel.text = Utils.durationFromSecs(metaData["Audio:Duration"]);
                }
                catch (e) {
                    durationLabel.clear();
                }

                root.showProgressIndicator = false;
                break;
            }
            case 3: {
                root.showProgressIndicator = false;
                break;
            }
            default:
                root.showProgressIndicator = false;
                break;
            }
        }
    }

    onAccepted: request.setMetaData(
        {
            "Audio:Artist": artistField.text,
            "Audio:Title": titleField.text
        }
    )
}
