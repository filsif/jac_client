#include "loginquery.h"
#include <QNetworkRequest>
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


    if (m_reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Network error. Error code is : " << m_reply->error();

        logged = false;
    }
    else
    {
        qDebug()<< "REPLY " << m_reply->readAll();

        logged = true;


    }



    emit results( this, logged);

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
