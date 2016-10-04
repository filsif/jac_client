#ifndef MYBOARDGAMESQUERY_H
#define MYBOARDGAMESQUERY_H

#include <QObject>


#include <QObject>
#include <QNetworkReply>
#include <QString>

#include "boardgamedata.h"

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

public :
     inline const QList< BoardGameData *> & datas    ( ) const { return m_list; }
protected :



    JacClient &             m_client;
    QNetworkReply *         m_reply;
    QList< BoardGameData *> m_list;

private slots:

    void                on_my_boardgames_finished          ( );
};
}

#endif // MYBOARDGAMESQUERY_H
