import QtQuick 2.0

import QtQuick.Controls 2.0

SwipeDelegate
{
    id: boardgameDelegate

    property string name
    property bool isSelected: listView.currentIndex === index

    width:  parent.width
    height: 128
    //z: isSelected ? 1000 : -index
    //rotation: isSelected ? 0 : -15
    //scale: isSelected ? 1.0 : 0.8
/*
    Behavior on rotation {
        NumberAnimation { duration: 500; easing.type: Easing.OutBack }
    }*/

    /*Behavior on scale {
        NumberAnimation { duration: 1000; easing.type: Easing.OutElastic }
    }*/

    Row{
        anchors.fill: parent
        Image {
            id      : imageItem
            width   : 128
            height  : 128
            source   : "file:///" + model.thumbnail
        }

        Text {
            anchors.centerIn: parent
            id      : textItem
            text    : model.title
        }
    }

    Component {
       id: removeComponent

       Rectangle {
           color: boardgameDelegate.swipe.complete && boardgameDelegate.pressed ? "#333" : "#444"
           width: parent.width
           height: parent.height
           clip: true

           Label {
               font.pixelSize: boardgameDelegate.font.pixelSize
               text: "Remove"
               color: "white"
               anchors.centerIn: parent
           }
       }
   }

   swipe.left: removeComponent
   swipe.right: removeComponent


}
