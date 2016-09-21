#ifndef JACCLIENT_H
#define JACCLIENT_H

#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QUrlQuery>
#include <QHttpMultiPart>


// queries

#include "loginquery.h"
#include "logoutquery.h"
#include "addboardgamequery.h"
#include "checknicknamequery.h"
#include "checkemailquery.h"

// libbgg

#include <libbgg/models.h>

namespace jac
{

class JacClient : public QObject
{
    Q_OBJECT
signals:

    void                            login                               ( );
    void                            logout                              ( );
    void                            nicknameAlreadyExists               ( bool );
    void                            emailAlreadyExists                  ( bool );
public:
                                    JacClient                           ( QObject * parent  = Q_NULLPTR);
    virtual                         ~JacClient                          ( );


    // public access

    int                             loginJac                            ( QString  , QString );
    int                             logoutJac                           ( );
    int                             checkNickname                       ( QString );
    int                             checkEmail                          ( QString );


    int                             addBoardGame                        ( Bgg::BoardGameInfo_sp bg_info );



    QString                         baseUrl                             ( ){ return m_baseUrl;}
    QNetworkReply *                 getReply                            ( QNetworkRequest & request);
    QNetworkReply *                 postReply                           ( QNetworkRequest & request , QHttpMultiPart * params);

private :

    QMutex *                        m_mutex;
    QNetworkAccessManager *         m_qnam;
    bool                            m_logged;
    QString                         m_baseUrl;

private slots:


    void                            on_result_login_finished             ( LoginQuery * , bool );
    void                            on_result_logout_finished            ( LogoutQuery * );
    void                            on_result_boardgame_added            ( AddBoardGameQuery * );
    void                            on_result_check_nickname             ( CheckNicknameQuery *, bool );
    void                            on_result_check_email                ( CheckEmailQuery *,bool );
};

}

#endif // JACCLIENT_H
