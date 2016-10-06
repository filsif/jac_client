#include "myboardgameimagesquery.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "boardgamedata.h"
#include "jacclient.h"

namespace jac
{

MyBoardGameImagesQuery::MyBoardGameImagesQuery(JacClient & jac , BoardGameData * data) :
  m_client(jac)
  ,m_reply(Q_NULLPTR)
 ,m_data(data)
  {


      QUrl url;

      url = url.resolved( data->thumbnail() );


      QNetworkRequest request;
      request.setUrl(url);

      qDebug() << "Start My Boardgame Image Query on : " << url.toString();


      m_reply = jac.getReply( request  );

      connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_my_boardgame_images_finished()));

  }

MyBoardGameImagesQuery::~MyBoardGameImagesQuery()
{

}


void
MyBoardGameImagesQuery::on_my_boardgame_images_finished()
{
  if (m_reply->error() != QNetworkReply::NoError)
  {
      qWarning() << "Network error. Error code is : " << m_reply->error();
  }
  else
  {
      QPixmap pixmap;
      pixmap.loadFromData( m_reply->readAll());
      if (!pixmap.isNull())
      {
          m_data->setImage( Bgg::Thumbnail ,pixmap );
          emit results(this);
      }

  }

  m_reply->deleteLater();
  m_reply = Q_NULLPTR;
}

}
