#ifndef CHECKEMAILQUERY_H
#define CHECKEMAILQUERY_H

#include <QObject>
#include <QNetworkReply>
#include <QString>

// libbgg

#include <libbgg/models.h>

namespace jac
{
class JacClient;

class CheckEmailQuery : public QObject
{
    Q_OBJECT
public:
    explicit CheckEmailQuery(JacClient & jac , QString );

    virtual  ~CheckEmailQuery                 ( );

signals :

    void                results                     ( CheckEmailQuery * , bool  );

protected :


    JacClient &             m_client;
    QString                 m_email;
    QNetworkReply *         m_reply;

private slots:

    void                on_check_email_finished          ( );
};
}

#endif // CHECKEMAILQUERY_H
