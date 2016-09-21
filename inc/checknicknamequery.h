#ifndef CHECKNICKNAMEQUERY_H
#define CHECKNICKNAMEQUERY_H

#include <QObject>
#include <QNetworkReply>
#include <QString>

// libbgg

#include <libbgg/models.h>

namespace jac
{
class JacClient;


class CheckNicknameQuery : public QObject
{
    Q_OBJECT

public:
    explicit CheckNicknameQuery(JacClient & jac, QString );

    virtual  ~CheckNicknameQuery                 ( );

signals :

    void                results                     ( CheckNicknameQuery *, bool  );

protected :


    JacClient &             m_client;
    QString                 m_nickname;
    QNetworkReply *         m_reply;

private slots:

    void                on_check_nickname_finished          ( );
};

}

#endif // CHECKNICKNAMEQUERY_H
