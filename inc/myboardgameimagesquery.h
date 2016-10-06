#ifndef MYBOARDGAMEIMAGESQUERY_H
#define MYBOARDGAMEIMAGESQUERY_H

#include <QObject>
#include <QNetworkReply>
#include <QString>

#include "boardgamedata.h"

// libbgg

#include <libbgg/models.h>

namespace jac
{
class JacClient;

class MyBoardGameImagesQuery : public QObject
{
    Q_OBJECT
public:
    explicit MyBoardGameImagesQuery(JacClient & jac , BoardGameData * data);

    virtual  ~MyBoardGameImagesQuery                 ( );

signals :

    void                results                     ( MyBoardGameImagesQuery *  );

public :

protected :



    JacClient &             m_client;
    QNetworkReply *         m_reply;
    BoardGameData *         m_data;


private slots:

    void                on_my_boardgame_images_finished          ( );
};
}




#endif // MYBOARDGAMEIMAGESQUERY_H
