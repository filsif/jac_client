import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0


Row{
    id: container
    anchors.left: parent.left
    anchors.right: parent.right

    spacing : 5

    property bool canBeEmpty    : true
    property bool isHidden      : false
    property string phText
    property string myText      : textInscription.text
    signal checkValue( string str )

    TextField {
        id                          : textInscription
        width                       : parent.width - 150
        height                      : 32
        x                           : 25
        color                       : "#000000"
        font.pixelSize              : 12
        placeholderText             : container.phText
        echoMode                    : {
                                        if ( isHidden )
                                            return TextInput.Password
                                        else
                                            return TextInput.Normal
                                        }
        background: Rectangle{
            color :"white"
            border.color: textInscription.enabled ? "#0083b3" : "#c0c0c0"
            radius : 3
        }

        onEditingFinished:{

            // verifier que le nickname n'est pas déjà pris

            if ( textInscription.text == "" && !canBeEmpty  )
            {
                imageSuccess.visible = false
                imageWrong.visible = true
                textInfo.text = "Cannot be empty"
            }
            else
            {
                container.checkValue( textInscription.text   )
            }
        }
       /* MouseArea {
            anchors.fill: parent
            id : mousearea

            onClicked:{
                imageSuccess.visible = false
                imageWrong.visible = false
                textInfo.text = ""

            }
        }*/
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

    Text{
        id      : textInfo
        height  : 32

        color   : "red"
    }

    function updateCheck(obj , txt )
    {        
        if ( obj === false )
        {
            imageSuccess.visible = true
            imageWrong.visible = false
            textInfo.text = ""
        }
        else
        {
            imageSuccess.visible = false
            imageWrong.visible = true
            textInfo.text = txt
        }
    }
}
