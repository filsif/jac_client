import QtQuick 2.0

import fr.jac.client 1.0

Item {

    // Footer

    // *** MovieDataModel implemented in C++ side ***
    BoardGameDataModel{
        id: boardgameModel
    }


    ListView {
        property int nb_results: 0
        property int totalResults:0

        id: listView
        width: parent.width; height: parent.height
        anchors.fill: parent

        model: boardgameModel
        delegate:BoardGameDelegate {
            id: boardgameDelegate
            name: model.title
        }

        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 400
        preferredHighlightBegin: 50
        preferredHighlightEnd: 100
        cacheBuffer: 4000

        onCurrentIndexChanged: {
            console.log("currentIndex: ", currentIndex)
        }
    }



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
                   mainWidget.refreshBoardGames()

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

            // *** MovieData object raised, insert it in the model ! ***
            onBoardGameData: {
                boardgameModel.addBoardGame(boardgame)
                listView.nb_results += 1
            }


        }        

    }

}
