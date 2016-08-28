#include "logoutquery.h"
#include <QNetworkRequest>
#include "jacclient.h"


namespace jac
{
LogoutQuery::LogoutQuery( JacClient & jac ):
m_client(jac)
,m_reply(Q_NULLPTR)
{

    QUrl url = m_client.baseUrl();
    QString str = QString("logout/");
    url = url.resolved( str );

    qDebug() << "Start Logout Query on : " << url.toString();
    QNetworkRequest request;
    request.setUrl(url);
    m_reply = jac.getReply( request );
    connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_logout_finished()));

}

LogoutQuery::~LogoutQuery()
{
    qDebug() << "Destroy Logout Query";

}


void
LogoutQuery::on_logout_finished()
{


    if (m_reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Network error. Error code is : " << m_reply->error();
    }
    else
    {
        qDebug()<< "REPLY " << m_reply->readAll();
        emit results( this );
    }

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
