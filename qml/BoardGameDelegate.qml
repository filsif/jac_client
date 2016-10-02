import QtQuick 2.0

Item
{
    id: boardgameDelegate

    property string name
    property bool isSelected: listView.currentIndex === index

    width: parent ? parent.width : imageItem.width
    height: imageItem.height
    z: isSelected ? 1000 : -index
    rotation: isSelected ? 0 : -15
    scale: isSelected ? 1.0 : 0.8

    Behavior on rotation {
        NumberAnimation { duration: 500; easing.type: Easing.OutBack }
    }

    Behavior on scale {
        NumberAnimation { duration: 1000; easing.type: Easing.OutElastic }
    }

    Text {
        id : textItem
        text : model.title
    }


}
