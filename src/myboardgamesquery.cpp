#include "inc/myboardgamesquery.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "jacclient.h"

namespace jac
{

MyBoardGamesQuery::MyBoardGamesQuery(JacClient & jac ) :
  m_client(jac)
  ,m_reply(Q_NULLPTR)
  {


      QUrl url = m_client.baseUrl();
      QString str = QString("player/boardgames/");
      url = url.resolved( str );


      QNetworkRequest request;
      request.setUrl(url);

      qDebug() << "Start My Boardgame Query on : " << url.toString();


      m_reply = jac.getReply( request  );

      connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_my_boardgames_finished()));

  }

MyBoardGamesQuery::~MyBoardGamesQuery()
{

}


void
MyBoardGamesQuery::on_my_boardgames_finished()
{
  if (m_reply->error() != QNetworkReply::NoError)
  {
      qWarning() << "Network error. Error code is : " << m_reply->error();
  }
  else
  {
      QJsonParseError error;


      QJsonDocument jsonResponse = QJsonDocument::fromJson( m_reply->readAll(),&error );
      if ( !jsonResponse.isEmpty() )
      {
            QJsonArray array = jsonResponse.array();

            if ( !array.isEmpty())
            {
                foreach (const QJsonValue & value, array)
                {
                    QJsonObject obj = value.toObject();
                    BoardGameData * data= new BoardGameData();
                    data->setBoardGameInfo( obj );
                    m_list << data;
                }
            }            
            emit results(this);
      }
  }

  m_reply->deleteLater();
  m_reply = Q_NULLPTR;
}

}
