import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0

Rectangle{
    id : pageInscription
    anchors.fill: parent
    color : "#00aff0"
    Column
    {

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height / 3
        anchors.horizontalCenter: parent.horizontalCenter

        width : parent.width
        spacing : 5


        RowInscription{
            id : nickname
            canBeEmpty : false
            phText : "Pseudo Jouons à Châteauroux"



        }

        RowInscription{
            id : email
            anchors.top : nickname.bottom
            canBeEmpty : false
            phText : "E-mail"
        }


/*

        TextField {
            id                          : email
            width                       : parent.width - 150
            height                      : 30
            x                           : 25
            color                       : "#000000"
            font.pixelSize              : 12
            placeholderText             : "e-mail"
            background: Rectangle{
                color :"white"
                border.color: email.enabled ? "#0083b3" : "#c0c0c0"
                radius : 3
            }

            onEditingFinished:{
                if ( email.text == "" )
                {

                }
                else
                {
                    mainWidget.CheckEmail( email.text )
                }
            }
        }

        TextField {
            id                          : password
            width                       : parent.width - 150
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

            onEditingFinished:{
                console.log( password.text )
            }
        }

            TextField {
                id                          : passwordconfirm
                width                       : parent.width - 50
                x                           : 25
                height                      : 30
                color                       : "#000000"
                font.pixelSize              : 12
                echoMode                    : TextInput.Password
                placeholderText             : "Confirmer mot de passe"
                background: Rectangle{
                    color :"white"
                    border.color: passwordconfirm.enabled ? "#0083b3" : "#c0c0c0"
                    radius : 3
                }

                onEditingFinished:{
                    console.log( passwordconfirm.text )
                }
        }


*/
        Connections{
            target : nickname
            onCheckValue:{

                mainWidget.CheckNickname( str )
            }
        }

        Connections{
            target : email
            onCheckValue:{

                mainWidget.CheckEmail( str )
            }
        }

        Connections{
            target : mainWidget

            onNicknameExists:{

                nickname.updateCheck( result , "Already exists" )
            }
            onEmailExists:{
                email.updateCheck( result , "Already exists")

            }
        }



    }

}
