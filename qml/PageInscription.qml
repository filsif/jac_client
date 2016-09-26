import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0

Rectangle{
    id : pageInscription
    anchors.fill: parent
    color : "#00aff0"
    QtObject
    {
        id : inscriptionDatas

        property string username    : username.myText
        property string email       : email.myText
        property string password    : password.myText
        property string firstname   : firstname.myText
        property string lastname    : lastname.myText
        property string address     : address.myText
        property string birthdate   : birthdate.myText
        property string mobilephone : mobilephone.myText
        property string bggnick     : bggnick.myText
    }

    Column
    {
        width : parent.width
        spacing : 5

        RowInscription{
            id : username
            canBeEmpty : false
            phText : qsTr("Pseudo Jouons à Châteauroux")
        }
        RowInscription{
            id : email
            anchors.top : username.bottom
            canBeEmpty : false
            phText : qsTr("E-mail")
        }
        RowInscription{
            id : password
            anchors.top : email.bottom
            canBeEmpty: false
            isHidden : true
            phText : qsTr("Mot de passe")
        }
        RowInscription{
            id : passwordconfirm
            anchors.top : password.bottom
            canBeEmpty: false
            isHidden : true
            phText : qsTr("Confirmer mot de passe")
        }
        RowInscription{
            id : firstname
            anchors.top : passwordconfirm.bottom
            phText : qsTr("Prénom")
        }
        RowInscription{
            id : lastname
            anchors.top : firstname.bottom
            phText : qsTr("Nom")
        }
        RowInscription{
            id : birthdate
            anchors.top : lastname.bottom
            phText : qsTr("Date de naissance")
        }
        RowInscription{
            id : address
            anchors.top : birthdate.bottom
            phText : qsTr("Adresse")
        }
        RowInscription{
            id : mobilephone
            anchors.top : address.bottom
            phText : qsTr("Numéro de mobile")
        }
        RowInscription{
            id : bggnick
            anchors.top : mobilephone.bottom
            phText : qsTr("Pseudo Board Game Geek")
        }


        LoginButton{
            anchors.top : bggnick.bottom
            id : buttonCreer
            text : "Créer"
            width: parent.width - 100
            x : 50
            height: 30
            disabled: false
            onClicked:{
                mainWidget.CreateUser( inscriptionDatas )
            }

        }



        Connections{
            target : username
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
            target : password
            onCheckValue:{

                if ( str !== passwordconfirm.myText )
                {

                    password.updateCheck( true , qsTr("password did not match") )
                    passwordconfirm.updateCheck( true , qsTr("password did not match") )
                }
                else
                {

                    password.updateCheck( false  )
                    passwordconfirm.updateCheck( false  )

                }
            }
        }
        Connections{
            target : passwordconfirm
            onCheckValue:{

                if ( str !== password.myText )
                {
                    password.updateCheck( true , qsTr("password did not match") )
                    passwordconfirm.updateCheck( true , qsTr("password did not match") )
                }
                else
                {
                    password.updateCheck( false )
                    passwordconfirm.updateCheck( false  )
                }
            }
        }

        Connections{
            target : mainWidget

            onNicknameExists:{

                nickname.updateCheck( result , qsTr("Already exists") )
            }
            onEmailExists:{
                email.updateCheck( result , qsTr("Already exists") )

            }
        }



    }

}
