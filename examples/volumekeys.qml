import QtQuick 1.0
import org.hildon.components 1.0

Window {
    id: window

    visible: true
    title: "VolumeKeys"

    VolumeKeys.enabled: true

    Rectangle {
        color: "blue"
        width: 50
        height: 50
        anchors.centerIn: parent
        focus: true

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_F7:
                rect.scale += 0.1;
                break;
            case Qt.Key_F8:
                rect.scale -= 0.1;
                break;
            default:
                return;
            }

            event.accepted = true;
        }
    }
}
