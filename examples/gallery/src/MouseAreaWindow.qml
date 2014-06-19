import org.hildon.components 1.0

Window {
    id: root

    windowTitle: qsTr("MouseArea")

    Column {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }

        ValueButton {
            id: selector

            text: qsTr("Drag axis")
            valueText: "XAxis"
            selector: ListSelector {
                model: [ "XAxis", "YAxis", "XandYAxis" ]
                currentIndex: 2
                onSelected: mouseArea.drag.axis = currentValueText
            }
        }
    }

    Label {
        id: label

        y: 100
        width: 200
        height: 40
        color: platformStyle.activeTextColor
        font.bold: true
        font.pixelSize: 32
        text: qsTr("Drag me")
    }

    MouseArea {
        id: mouseArea

        anchors {
            fill: parent
            topMargin: 100
        }
        drag.target: label
        drag.axis: "XAxis"
    }
}
