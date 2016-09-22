import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0


Row{
    id: container
    anchors.left: parent.left
    anchors.right: parent.right

    spacing : 5

    property bool canBeEmpty : True
    property string phText
    signal checkValue( string str )

    TextField {
        id                          : textInscription
        width                       : parent.width - 150
        height                      : 32
        x                           : 25
        color                       : "#000000"
        font.pixelSize              : 12
        placeholderText             : container.phText
        background: Rectangle{
            color :"white"
            border.color: nickname.textInscription ? "#0083b3" : "#c0c0c0"
            radius : 3
        }

        onEditingFinished:{

            // verifier que le nickname n'est pas déjà pris

            if ( textInscription.text == "" && !canBeEmpty  )
            {
                imageSuccess.visible = false
                imageWrong.visible = true
            }
            else
            {
                container.checkValue( textInscription.text   )
            }
        }
    }
    Image{
        id       : imageSuccess
        width    : 32
        height   : 32
        source   : "qrc:///images/success.png"
        visible  : false
    }

    Image{
        id       : imageWrong
        width    : 32
        height   : 32
        source   : "qrc:///images/close.png"
        visible  : false
    }

    function updateCheck(obj)
    {
        console.log( "tutu " + obj)
        if ( obj === false )
        {
            imageSuccess.visible = true
            imageWrong.visible = false
        }
        else
        {
            imageSuccess.visible = false
            imageWrong.visible = true
        }
    }
}
