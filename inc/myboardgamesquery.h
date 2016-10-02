#ifndef MYBOARDGAMESQUERY_H
#define MYBOARDGAMESQUERY_H

#include <QObject>


#include <QObject>
#include <QNetworkReply>
#include <QString>

// libbgg

#include <libbgg/models.h>

namespace jac
{
class JacClient;

class MyBoardGamesQuery : public QObject
{
    Q_OBJECT
public:
    explicit MyBoardGamesQuery(JacClient & jac );

    virtual  ~MyBoardGamesQuery                 ( );

signals :

    void                results                     ( MyBoardGamesQuery *  );

protected :


    JacClient &             m_client;
    QNetworkReply *         m_reply;

private slots:

    void                on_my_boardgames_finished          ( );
};
}

#endif // MYBOARDGAMESQUERY_H
