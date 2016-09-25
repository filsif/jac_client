#ifndef CREATEUSERQUERY_H
#define CREATEUSERQUERY_H




#include <QObject>
#include <QNetworkReply>

// libbgg

#include <libbgg/models.h>

namespace jac
{
class JacClient;


class CreateUserQuery : public QObject
{
    Q_OBJECT
public:
                        CreateUserQuery                  ( JacClient & jac,  QObject * datas );
    virtual             ~CreateUserQuery                 ( );

signals :

    void                results                     ( CreateUserQuery *, bool );

protected :


    JacClient &             m_client;
    QNetworkReply *         m_reply;

private slots:

    void                on_create_user_finished          ( );


};

}



#endif // CREATEUSERQUERY_H
