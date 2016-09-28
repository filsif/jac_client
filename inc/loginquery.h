#ifndef LOGINQUERY_H
#define LOGINQUERY_H

#include <QObject>
#include <QNetworkReply>

namespace jac
{
class JacClient;


class LoginQuery : public QObject
{
    Q_OBJECT
public:
                        LoginQuery                  ( JacClient & jac,  QString & login , QString & password);
    virtual             ~LoginQuery                 ( );

signals :

    void                results                     ( LoginQuery * , bool logged , QString & bgg_nick);

protected :


    JacClient &         m_client;
    QString             m_login;
    QString             m_password;
    QNetworkReply *     m_reply;

private slots:

    void                on_login_finished           ( );


};

}

#endif // LOGINQUERY_H
