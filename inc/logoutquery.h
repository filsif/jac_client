#ifndef LOGOUTQUERY_H
#define LOGOUTQUERY_H

#include <QObject>
#include <QNetworkReply>

namespace jac
{
class JacClient;


class LogoutQuery : public QObject
{
    Q_OBJECT
public:
                        LogoutQuery                  ( JacClient & jac );
    virtual             ~LogoutQuery                 ( );

signals :

    void                results                     ( LogoutQuery *  );

protected :


    JacClient &         m_client;
    QNetworkReply *     m_reply;

private slots:

    void                on_logout_finished           ( );


};

}

#endif // LOGINQUERY_H
