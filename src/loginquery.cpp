#include "loginquery.h"
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "jacclient.h"


namespace jac
{
LoginQuery::LoginQuery( JacClient & jac , QString &login , QString &password):
m_client(jac)
,m_login(login)
,m_password(password)
,m_reply(Q_NULLPTR)
{

    QUrl url = m_client.baseUrl();
    QString str = QString("login/%1/%2/").arg( m_login , m_password );
    url = url.resolved( str );

    qDebug() << "Start Login Query on : " << url.toString();
    QNetworkRequest request;
    request.setUrl(url);
    m_reply = jac.getReply( request );
    connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_login_finished()));

}

LoginQuery::~LoginQuery()
{
    qDebug() << "Destroy Login Query";

}


void
LoginQuery::on_login_finished()
{

    bool logged = false;
    QString bgg_nick("");


    if (m_reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Network error. Error code is : " << m_reply->error();

        logged = false;
    }
    else
    {
        /*
         [
            {"model": "auth.user", "pk": 1, "fields":
                                                {   "first_name": "Fr\u00e9d\u00e9ric",
                                                    "last_name": "MAZUR"
                                                }
            },
            {"model": "server.player", "pk": 1, "fields":
                                                {   "address": "1 La Roche 36350 La P\u00e9rouille",
                                                    "bgg_nickname": "filsif"
                                                }
            }
         ]

        */



        QJsonDocument jsonResponse = QJsonDocument::fromJson( m_reply->readAll() );
        if ( !jsonResponse.isEmpty() )
        {

              QJsonArray jsonArray = jsonResponse.array();
              foreach (const QJsonValue & value, jsonArray)
              {
                   QJsonObject obj = value.toObject();

                   if ( obj["model"].toString().compare("server.player") == 0)
                   {
                       QJsonValue fields = obj["fields"];

                       QJsonObject field_obj = fields.toObject();

                       bgg_nick = field_obj["bgg_nickname"].toString();


                   }

              }
        }

        logged = true;


    }



    emit results( this, logged , bgg_nick );

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
