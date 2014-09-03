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

Page {
    id: root

    windowTitle: qsTr("ListView")

    ListView {
        id: view

        width: parent.width
        height: parent.height
        model: [
            { title: "Classic Game Room - ACCLAIM DUAL TURBO SNES Controller review", subTitle: "This is a list item", duration: "01:32", thumbnail: "file:///home/user/MyDocs/Classic Game Room - ACCLAIM DUAL TURBO SNES Controller review.jpg", progress: 17 },
        { title: "Classic Game Room - CASTLEVANIA CIRCLE OF THE MOON review", subTitle: "This is another list item", duration: "03:13", thumbnail: "file:///home/user/MyDocs/Classic Game Room - CASTLEVANIA_ CIRCLE OF THE MOON review.jpg", progress: 84 },
        { title: "Classic Game Room - CRYSIS 3 review", subTitle: "And another list item", duration: "06:43", thumbnail: "file:///home/user/MyDocs/Classic Game Room - CRYSIS 3 review.jpg", progress: 56 },
        { title: "Classic Game Room - PANASONIC 3DO console review model FZ-1", subTitle: "And another list item", duration: "10:15", thumbnail: "file:///home/user/MyDocs/Classic Game Room - PANASONIC 3DO console review model FZ-1.jpg", progress: 34 },
        { title: "Classic Game Room - SQUEEZE BOX review for Atari 2600", subTitle: "This is the last list item", duration: "07:27", thumbnail: "file:///home/user/MyDocs/Classic Game Room - SQUEEZE BOX review for Atari 2600.jpg", progress: 29 }
        ]
        delegate: ListItem {
            width: view.width
            height: 90

            ListItemImage {
                anchors.fill: parent
                source: isCurrentItem ? "file:///etc/hildon/theme/images/TouchListBackgroundPressed.png"
                                      : "file:///etc/hildon/theme/images/TouchListBackgroundNormal.png"
            }

            ListItemText {
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    right: progressBar.left
                    margins: 10
                }
                alignment: Qt.AlignLeft | Qt.AlignVCenter
                text: modelData.title + "\n" + modelData.subTitle
            }

            ListItemProgressBar {
                id: progressBar

                width: 150
                height: 70
                anchors {
                    right: parent.right
                    rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                maximum: 100
                progress: modelData.progress
                text: progress + "%"
                textVisible: true
                textAlignment: Qt.AlignCenter
            }
        }
    }
}
