#include "jacclient.h"
#include <QNetworkRequest>



namespace jac
{

JacClient::JacClient( QObject *parent)
 : QObject(parent)
 ,m_mutex(Q_NULLPTR)
 ,m_qnam( Q_NULLPTR)
 ,m_logged(false)
{
    m_mutex = new QMutex;
    m_qnam = new QNetworkAccessManager(this);
    //m_baseUrl = "http://fmr-dev.net:8000/server/";
    m_baseUrl = "http://127.0.0.1:8000/server/";
}



JacClient::~JacClient()
{
    delete m_mutex;
    delete m_qnam;
}


QNetworkReply *
JacClient::getReply(QNetworkRequest & request)
{
    QMutexLocker locker( m_mutex );

    return m_qnam->get(request);
}

QNetworkReply *
JacClient::postReply(QNetworkRequest & request , QUrlQuery &params)
{
    QMutexLocker locker( m_mutex );

    return m_qnam->post(request , params.toString().toUtf8() );


}

int
JacClient::loginJac( QString login , QString  password )
{

    LoginQuery *query = new LoginQuery(*this,  login, password );

    connect ( query , SIGNAL(results(LoginQuery * , bool)) , this , SLOT(on_result_login_finished(LoginQuery * , bool)));

    return 0;
}

void
JacClient::on_result_login_finished( LoginQuery *query, bool logged)
{
    if ( logged )
    {
        emit login();
    }

    query->deleteLater();

}

int
JacClient::logoutJac()
{

    LogoutQuery *query = new LogoutQuery(*this  );

    connect ( query , SIGNAL(results(LogoutQuery * )) , this , SLOT(on_result_logout_finished(LogoutQuery * )));


     return 0;

}


void
JacClient::on_result_logout_finished( LogoutQuery *query )
{
    emit logout();
    query->deleteLater();

}


/*
add boardgame
*/

int
JacClient::addBoardGame( Bgg::BoardGameInfo_sp bg_info )
{
    AddBoardGameQuery *query = new AddBoardGameQuery( *this , bg_info );

    connect ( query , SIGNAL(results(AddBoardGameQuery * )) , this , SLOT(on_result_boardgame_added(AddBoardGameQuery * )));


    return 0;

}


void
JacClient::on_result_boardgame_added(AddBoardGameQuery * query )
{
    qDebug() << "game added !!!";
    query->deleteLater();

}




}

