import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import Qt.labs.settings 1.0

Item
{
    id : mainpage
    visible: true
    width: 600
    height: 800



    QtObject
    {
        id : infos
    }

    state : "LOGIN"
    PageLogin{
        id                  : pageLogin
        anchors.centerIn    : parent
        visible             : true
        opacity             : 0.0

    }
    PagePrincipale{
        id                  : pagePrincipale
        anchors.centerIn    : parent
        visible             : false
        opacity             : 0.0
    }
    PageInscription{
        id                  : pageInscription
        anchors.centerIn    : parent
        visible             : false
        opacity             : 0.0
    }

    states: [
        State {
            name: "LOGIN"
            PropertyChanges { target: pageLogin; opacity : 1.0;visible : true }
            PropertyChanges { target: pagePrincipale; opacity : 0.0 ; visible : false }
            PropertyChanges { target: pageInscription; opacity : 0.0 ; visible : false }
        },
        State {
            name: "PRINCIPALE"
            PropertyChanges { target: pageLogin; opacity : 0.0 ; visible : false}
            PropertyChanges { target: pagePrincipale; opacity : 1.0 ;visible : true}
        },
        State {
            name: "INSCRIPTION"
            PropertyChanges { target: pageLogin; opacity : 0.0 ; visible : false}
            PropertyChanges { target: pageInscription; opacity : 1.0 ;visible : true}

        }

    ]

    transitions: [
        Transition {
            from: "LOGIN"; to: "PRINCIPALE"; reversible: true
            ParallelAnimation {
                NumberAnimation { properties: "opacity,visible"; duration: 500; easing.type: Easing.InOutQuad }
                ColorAnimation { duration: 500 }
            }
        },
        Transition {
            from: "LOGIN"; to: "INSCRIPTION"; reversible: true
            ParallelAnimation {
                NumberAnimation { properties: "opacity,visible"; duration: 500; easing.type: Easing.InOutQuad }
                ColorAnimation { duration: 500 }
            }
        }]




}

