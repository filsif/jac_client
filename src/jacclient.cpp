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
    //m_baseUrl = "http://192.168.1.249:8000/server/";
    //m_baseUrl = "http://172.17.10.140:8000/server/";
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
JacClient::postReply(QNetworkRequest & request , QHttpMultiPart *params)
{
    QMutexLocker locker( m_mutex );

    //return m_qnam->post(request , params.query(QUrl::FullyEncoded).toUtf8() );
    return m_qnam->post(request , params );


}

int
JacClient::loginJac( QString login , QString  password )
{
    LoginQuery *query = new LoginQuery(*this,  login, password );
    connect ( query , SIGNAL(results(LoginQuery * , bool)) , this , SLOT(on_result_login_finished(LoginQuery * , bool)));
    return 0;
}

int
JacClient::logoutJac()
{
    LogoutQuery *query = new LogoutQuery(*this  );
    connect ( query , SIGNAL(results(LogoutQuery * )) , this , SLOT(on_result_logout_finished(LogoutQuery * )));
    return 0;
}

int
JacClient::checkNickname( QString nickname )
{
    CheckNicknameQuery *query = new CheckNicknameQuery( *this , nickname );
    connect ( query , SIGNAL(results(CheckNicknameQuery * , bool )) , this , SLOT(on_result_check_nickname(CheckNicknameQuery * , bool )));
    return 0;
}

int
JacClient::checkEmail( QString email)
{
    CheckEmailQuery *query = new CheckEmailQuery( *this , email );
    connect ( query , SIGNAL(results(CheckEmailQuery * , bool )) , this , SLOT(on_result_check_email(CheckEmailQuery * , bool )));
    return 0;
}

int
JacClient::createUser( QObject * datas)
{
    CreateUserQuery *query = new CreateUserQuery( *this , datas );
    connect ( query , SIGNAL(results(CreateUserQuery * , bool )) , this , SLOT(on_result_create_user(CreateUserQuery * , bool )));
    return 0;

}



int
JacClient::addBoardGame( Bgg::BoardGameInfo_sp bg_info )
{
    AddBoardGameQuery *query = new AddBoardGameQuery( *this , bg_info );
    connect ( query , SIGNAL(results(AddBoardGameQuery * )) , this , SLOT(on_result_boardgame_added(AddBoardGameQuery * )));
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



void
JacClient::on_result_logout_finished( LogoutQuery *query )
{
    emit logout();
    query->deleteLater();
}


void
JacClient::on_result_boardgame_added(AddBoardGameQuery * query )
{    
    query->deleteLater();
}


void
JacClient::on_result_check_nickname( CheckNicknameQuery * query ,bool already )
{
    qDebug()<<"prout";
    emit nicknameAlreadyExists( already );
    query->deleteLater();

}

void
JacClient::on_result_check_email( CheckEmailQuery * query ,bool already )
{
    emit emailAlreadyExists( already );
    query->deleteLater();
}

void
JacClient::on_result_create_user( CreateUserQuery * query ,bool created )
{
    emit userCreated( created );
    query->deleteLater();
}


}

