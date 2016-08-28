import QtQuick 2.7



Item {
    id: container

    property string text
    property bool disabled: false
    signal clicked

    // Suitable default size
    width: parent.width
    height: 60

    Rectangle {
        id: normal
        anchors.fill: parent
        border.color: "#0083b3"
        border.width: 1
        radius: 15
        smooth: true

        color : "#1ea1d1"
    }

    Rectangle {
        id: pressed
        anchors.fill: parent
        border.color: "#0083b3"
        border.width: 1
        radius: 15
        smooth: true
        opacity: 0

        color : "#46bae4"
    }

    Rectangle {
        id: disabled
        anchors.fill: parent
        border.color: "#0083b3"
        border.width: 1
        radius: 15
        smooth: true
        opacity: 0

        color : "#1ea1d1"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!container.disabled)
                container.clicked()
        }
        onPressed: {
            if (!container.disabled)
                container.state = "Pressed"
        }
        onReleased: {
            if (!container.disabled)
                container.state = ""
        }
    }

    Text {
        font.family: "Arial"
        font.pointSize: 12
        smooth: true
        color: {
            if (container.disabled)
                "#dddddd"
            else
                "#ffffff"
        }
        anchors.centerIn: parent
        text: container.text
    }

    states: [
    State {
        name: "Pressed"
        PropertyChanges { target: pressed; opacity: 1 }
    },
    State {
        name: "Disabled"
        when: container.disabled == true
        PropertyChanges { target: disabled; opacity: 1 }
    }
    ]
    transitions: Transition {
        NumberAnimation { properties: "opacity"; duration:100 }
    }

}

