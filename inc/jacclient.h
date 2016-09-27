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
#include "createuserquery.h"

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
    void                            nicknameAlreadyExists               ( bool result );
    void                            emailAlreadyExists                  ( bool result );
    void                            userCreated                         ( bool result );

public :
    // access to parameters of current logged user

    inline const QString &          bggNickname                         ( ) const { return m_bgg_nickname ; }
public:
                                    JacClient                           ( QObject * parent  = Q_NULLPTR);
    virtual                         ~JacClient                          ( );


    // public access

    int                             loginJac                            ( QString  , QString );
    int                             logoutJac                           ( );
    int                             checkNickname                       ( QString );
    int                             checkEmail                          ( QString );
    int                             createUser                          ( QObject *);


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
    void                            on_result_create_user                ( CreateUserQuery * , bool );


private :
    // parameters of current logged user
    QString                         m_bgg_nickname;
    QString                         m_firstname;
    QString                         m_lastname;
    QString                         m_username;
    QString                         m_address;
    QDate                           m_birthdate;
    QString                         m_email;
    QString                         m_mobile_phone;
};

}

#endif // JACCLIENT_H
