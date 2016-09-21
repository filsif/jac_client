#include "checknicknamequery.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include "jacclient.h"

namespace jac
{

CheckNicknameQuery::CheckNicknameQuery(JacClient & jac, QString nickname ) :
    m_client(jac)
    ,m_nickname(nickname)
    ,m_reply(Q_NULLPTR)
    {


        QUrl url = m_client.baseUrl();
        QString str = QString("player/nickname/%1/").arg( m_nickname );
        url = url.resolved( str );


        QNetworkRequest request;
        request.setUrl(url);


        m_reply = jac.getReply( request  );

        connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_check_nickname_finished()));

    }

CheckNicknameQuery::~CheckNicknameQuery()
{

}


void
CheckNicknameQuery::on_check_nickname_finished()
{


    if (m_reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Network error. Error code is : " << m_reply->error();
    }
    else
    {
        qDebug() <<"pouet " << m_reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson( m_reply->readAll() );
        if ( !jsonResponse.isEmpty() )
        {
            qDebug()<<"pip";
              QJsonObject jsonObject = jsonResponse.object();
              bool val = jsonObject.value("result").toBool();
              emit results( this , val );
        }
    }

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
