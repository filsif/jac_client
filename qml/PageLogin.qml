import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0


Rectangle{
    id : pageLogin
    anchors.fill: parent
    color : "#00aff0"

    Image  {
       id: jacLogo
       anchors.top: parent.top
       anchors.topMargin: 100
       source: "qrc:///images/logo.png"
       anchors.horizontalCenter: parent.horizontalCenter
    }

    Settings
    {
           property alias text : login.text
    }

    Column
    {

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height / 3
        anchors.horizontalCenter: parent.horizontalCenter

        width : parent.width
        spacing : 5    

        TextField {
            id                          : login
            width                       : parent.width - 50
            height                      : 30
            x                           : 25
            color                       : "#000000"
            font.pixelSize              : 12
            placeholderText             : "Pseudo Jouons à Châteauroux"
            background: Rectangle{
                color :"white"
                border.color: login.enabled ? "#0083b3" : "#c0c0c0"
                radius : 3
            }
        }

        TextField {
            id                          : password
            width                       : parent.width - 50
            x                           : 25
            height                      : 30
            color                       : "#000000"
            font.pixelSize              : 12
            echoMode                    : TextInput.Password
            placeholderText             : "Mot de passe"
            background: Rectangle{
                color :"white"
                border.color: password.enabled ? "#0083b3" : "#c0c0c0"
                radius : 3
            }
        }

        LoginButton{
            id : buttonLogin
            text : "Connexion"
            width: parent.width - 100
            x : 50
            height: 30
            disabled: false

            onClicked:{
                mainWidget.Login( login.text , password.text)
            }

        }

        LoginButton{
            id : buttonInscription
            text : "Inscription"
            width: parent.width - 100
            x : 50
            height: 30
            disabled: false
            onClicked:{
                mainWidget.Inscription()
            }

        }
    }

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
           id       : facebookLink
           width    : 50
           height   : 50
           source   : "qrc:///images/facebook.png"

           MouseArea {
               anchors.fill : parent
               onClicked: {
                   Qt.openUrlExternally("https://www.facebook.com/jouonsachateauroux")
               }
           }
        }
        Image  {
           id       : googleplusLink
           width    : 50
           height   : 50
           source   : "qrc:///images/google-plus.png"

           MouseArea {
               anchors.fill : parent
               onClicked: {
                   Qt.openUrlExternally("https://plus.google.com/+JouonsachateaurouxFr")
               }
           }
        }
    }

    Connections {
        target : mainWidget

        onLogin: {
            console.log( "logged" )

            mainpage.state = "PRINCIPALE"

            mainWidget.refreshBoardGames()

        }
        onInscription: {
            mainpage.state = "INSCRIPTION"
        }

    }





}
