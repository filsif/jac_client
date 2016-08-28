import QtQuick 2.4
import QtQuick.Controls 1.2


Item {
    id: menu

    signal menuItemClicked( string item, string page )
    property alias currentItem: listViewMenu.currentIndex

    ListModel {
        id: modelMenu
        ListElement {
            item: "page_jeu"
            icon: "qrc:/images/icon_game.png"
            page: "PageMyGame.qml"
        }
        ListElement {
            item: "page_profil"
            icon: "qrc:/images/man-6.png"
            page: "PageSettings.qml"
        }
        ListElement {
            item: "page_event"
            icon: "qrc:/images/icon_info.png"
            page: "PageAbout.qml"
        }
        ListElement {
            item: "page_joueurs"
            icon: "qrc:/images/team.png"
            page: "PageAbout.qml"
        }

        ListElement {
            item: "page_logout"
            icon: "qrc:/images/logout.png"
            page: "PageAbout.qml"
        }
    }

    function textItemMenu( item )
    {
        var textReturn = ""
        switch( item ) {
        case "page_jeu":
            textReturn = qsTr("Mes jeux")
            break;
        case "page_profil":
            textReturn = qsTr("Profil")
            break;
        case "page_event":
            textReturn = qsTr("Evénements")
            break;
        case "page_joueurs":
            textReturn = qsTr("Joueurs")
            break;

        case "page_logout":
            textReturn = qsTr("Quitter")
            break;
        case "log":
            textReturn = "Log"
            break;
        }
        return textReturn
    }

    Rectangle {
        id: logoWtapper
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width
        height: width*0.5
        color: "#303030"//palette.primary //"#3078fe" //this color is equal to the background of imgLogo
        clip: true
        Image {
            id: imgLogo
            source: "qrc:/images/nobody.png"
            height: parent.height
            //width: parent.width
            antialiasing: true
            smooth: true
            anchors.top: parent.top
            //anchors.left: parent.left
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.5
        }
    }
    Image {
        id: imgShadow
        anchors.top: logoWtapper.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 10*app.dp
        z: 4
        source: "qrc:/images/shadow_title.png"
    }
    ListView {
        id: listViewMenu
        anchors.top: logoWtapper.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        model: modelMenu
        delegate: componentDelegate
    }

    Component {
        id: componentDelegate

        Rectangle {
            id: wrapperItem
            height: 90*app.dp
            width: parent.width
            color: wrapperItem.ListView.isCurrentItem || ma.pressed ? palette.currentHighlightItem : "transparent"
            Image {
                id: imgItem
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 0.5*imgItem.width
                height: parent.height*0.8
                width: height
                source: icon
                visible: icon != ""
                smooth: true
                antialiasing: true
            }

            Label {
                id: textItem
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: imgItem.right
                anchors.leftMargin: 0.7*imgItem.width
                text: textItemMenu( item )
                font.pixelSize: 12 //parent.height*0.3
                color: wrapperItem.ListView.isCurrentItem ? palette.darkPrimary : palette.primaryText
            }


            MouseArea {
                id: ma
                anchors.fill: parent
                enabled: app.menuIsShown
                onClicked: {
                    if (item == "page_logout")
                    {
                        listViewMenu.currentIndex = 0 // reset
                        pagePrincipale.onMenu()
                        mainWidget.Logout()
                    }
                    else
                    {
                        listViewMenu.currentIndex = index
                        menu.menuItemClicked( item, page )
                    }

                }
            }
        }

    }
}

