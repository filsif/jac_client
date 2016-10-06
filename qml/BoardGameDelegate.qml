import QtQuick 2.0

Item
{
    id: boardgameDelegate

    property string name
    property bool isSelected: listView.currentIndex === index

    width:  parent.width
    height: 64
    z: isSelected ? 1000 : -index
    //rotation: isSelected ? 0 : -15
    scale: isSelected ? 1.0 : 0.8
/*
    Behavior on rotation {
        NumberAnimation { duration: 500; easing.type: Easing.OutBack }
    }*/

    Behavior on scale {
        NumberAnimation { duration: 1000; easing.type: Easing.OutElastic }
    }

    Row{
        Image {
            id      : imageItem
            width   : 64
            height  : 64
            source   : "qrc:///images/thumbnail_image_empty.png"
        }

        Text {
            id      : textItem
            text    : model.title
        }
    }


}
