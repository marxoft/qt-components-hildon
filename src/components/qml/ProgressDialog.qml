/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.0
import org.hildon.components 1.0

Dialog {
    id: root
    
    /*!
        \brief Whether the dialog gets hidden by reset().
        
        The default is \c true.
    */
    property bool autoClose: true
    
    /*!
        \brief Whether the dialog calls reset() as soon as value equals maximum.
        
        The default is \c true.
    */
    property bool autoReset: true
    
    /*!
        \type:string
        \brief The display text of the cancel button.
        
        If empty, the cancel button will be hidden. The default is 'Cancel' (translated).
    */
    property alias cancelButtonText: cancelButton.text
    
    /*!
        \type:string
        \brief The display text of the label.
        
        If empty (the default), the label will be hidden.
    */
    property alias labelText: label.text
    
    /*!
        \type:int
        \brief The maximum value of the progress bar.
    */
    property alias maximum: progressBar.maximum
    
    /*!
        \type:int
        \brief The minimum value of the progress bar.
    */
    property alias minimum: progressBar.minimum
    
    /*!
        \type:int
        \brief The length of time that must pass before the dialog appears.
        
        The default value is 4000 milliseconds.
    */
    property alias minimumDuration: timer.interval
    
    /*!
        \type:int
        \brief The current value of the progress bar.
    */
    property alias value: progressBar.value
    
    /*!
        \brief Whether the dialog was canceled.
    */
    property bool wasCanceled: false
    
    /*!
        \brief This signal is emitted when the dialog is canceled.
    */
    signal canceled
    
    /*!
        \brief Cancels and hides the dialog.
        
        \c wasCanceled becomes true until the dialog is reset.
        
        \sa wasCanceled
    */
    function cancel() {
        wasCanceled = true;
        canceled();
        close();
    }
    
    /*!
        \brief Resets the dialog, and hides it if \c autoClose is true.
        
        \sa autoClose, autoReset
    */
    function reset() {
        value = minimum;
        wasCanceled = false;
        timer.stop();
        
        if (autoClose) {
            close();
        }
    }
    
    title: " " // Prevent display of application name
    height: column.height + platformStyle.paddingMedium
    
    Column {
        id: column
        
        anchors {
            left: parent.left
            right: cancelButton.visible ? cancelButton.left : parent.right
            rightMargin: button.visible ? platformStyle.paddingMedium : 0
            top: parent.top
        }
        spacing: platformStyle.paddingMedium
        
        Label {
            id: label
            
            width: parent.width
            visible: text != ""
        }
        
        ProgressBar {
            id: progressBar
            
            width: parent.width
            onValueChanged: {
                if (value >= maximum) {
                    if (root.autoReset) {
                        root.reset();
                    }
                }
                else if ((value > minimum) && (!root.visible) && (root.minimumDuration > 0) && (!timer.running)) {
                    timer.start();
                }
            }
        }
    }
    
    Button {
        id: cancelButton
        
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        style: DialogButtonStyle {}
        text: qsTr("Cancel")
        visible: text != ""
        onClicked: root.cancel()
    }
    
    Timer {
        id: timer
        
        interval: 4000
        repeat: false
        onTriggered: if ((root.value > root.minimum) && (root.value < root.maximum)) root.open();
    }

    StateGroup {
        id: group

        states: State {
            name: "Portrait"
            when: screen.currentOrientation == Qt.WA_Maemo5PortraitOrientation

            AnchorChanges {
                target: column
                anchors.right: parent.right
            }

            PropertyChanges {
                target: column
                anchors.rightMargin: 0
            }

            PropertyChanges {
                target: cancelButton
                width: parent.width
            }

            PropertyChanges {
                target: root
                height: column.height + (cancelButton.visible ? cancelButton.height + platformStyle.paddingMedium * 2
                    : platformStyle.paddingMedium)
            }
        }
    }
    
    onVisibleChanged: timer.stop()
}
