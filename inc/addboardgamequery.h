#ifndef ADDBOARDGAMEQUERY_H
#define ADDBOARDGAMEQUERY_H

#include <QObject>
#include <QNetworkReply>

// libbgg

#include <libbgg/models.h>

namespace jac
{
class JacClient;


class AddBoardGameQuery : public QObject
{
    Q_OBJECT
public:
                        AddBoardGameQuery                  ( JacClient & jac,  Bgg::BoardGameInfo_sp bg_info );
    virtual             ~AddBoardGameQuery                 ( );

signals :

    void                results                     ( AddBoardGameQuery *  );

protected :


    JacClient &             m_client;
    Bgg::BoardGameInfo_sp   m_bg_infos;
    QNetworkReply *         m_reply;

private slots:

    void                on_add_boardgame_finished          ( );


};

}

#endif // ADDBOARDGAMEQUERY_H
