import QtQuick 2.0

Item {

    // Footer

    Row
    {
        id                  : footer
        width               : 100
        height              : 50
        anchors.bottom      : parent.bottom
        anchors.bottomMargin: 10
        anchors.rightMargin : 10
        anchors.right       : parent.right

        spacing : 5

        Image  {
           id       : addGame
           width    : 50
           height   : 50
           source   : "qrc:///images/add-1-icon.png"

           MouseArea {
               anchors.fill : parent
               onClicked: {
                   mainWidget.Search()


               }
           }
        }
        Image  {
           id       : addGameBgg
           width    : 50
           height   : 50
           source   : "qrc:///images/add-1-icon-bgg.png"

           MouseArea {
               anchors.fill : parent
               onClicked: {

               }
           }
        }

        Connections {
            target: mainWidget

            onSearchBegin: {
                console.log("<onSearchBegin>: clear everyting.")

            }

            // *** Initial search finished: get the BoardGameData for each result ***
            onSearchFetched: {
                console.log("<onSearchFetched>")
                mainWidget.SearchBoardGames(result)
            }


        }
    }

}
