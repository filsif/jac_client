#include "myboardgameimagesquery.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QCryptographicHash>

#include "boardgamedata.h"
#include "jacclient.h"

extern QString g_cachePath;
namespace jac
{



MyBoardGameImagesQuery::MyBoardGameImagesQuery(JacClient & jac , BoardGameData * data) :
  m_client(jac)
 ,m_reply(Q_NULLPTR)
 ,m_data(data)
{


    if (CheckMd5File( m_data->thumbnail() , m_data->thumbnail_md5()))
    {
        qDebug() << "already in cache " << m_data->thumbnail();
    }
    else
    {
        QUrl url;
        url = url.resolved( m_data->thumbnail_remote() );
        QNetworkRequest request;
        request.setUrl(url);
        qDebug() << "Start My Boardgame Image Query on : " << url.toString();
        m_reply = jac.getReply( request  );
        connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_my_boardgame_images_finished()));
    }
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
      QFile f(m_data->thumbnail());

      if ( f.open( QFile::WriteOnly))
      {
          f.write( m_reply->readAll() );
          f.close();
      }

      emit results(this , m_data);


  }

  m_reply->deleteLater();
  m_reply = Q_NULLPTR;
}

bool
MyBoardGameImagesQuery::CheckMd5File( const QString & filename , const QString & md5 )
{
    bool result = false;
    // first , test if file is already present and md5 is ok
    QFile f( filename );
    if ( f.exists() )
    {
        if (f.open(QFile::ReadOnly))
        {
            QCryptographicHash hash( QCryptographicHash::Md5 );
            if ( hash.addData( &f ) )
            {
                QByteArray r = hash.result();
                if ( r.toHex() == md5 )
                {
                    result = true;
                }

            }
            f.close();
        }
    }

    return result;

}

}
