#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QSharedPointer>
#include <QThread>

#include "mainwidget.h"
#include <libbgg/models.h>
#include <libbgg/bgg.h>





//////////////////////////////////////////////////////////////////////////////////////////////////////
MainWidget::MainWidget(QWindow *parent )
 : QQuickView(parent)
 , m_context( Q_NULLPTR)
 , m_client(Q_NULLPTR)
{
    setResizeMode(QQuickView::SizeRootObjectToView);

    // Init client access

    //qmlRegisterType<jac::JacClient>("jac.client", 1, 0, "jacClient");

    m_client = new jac::JacClient( );
    connect ( m_client , SIGNAL(login()) , this , SLOT(on_login()));
    connect ( m_client , SIGNAL(logout()) , this , SLOT(on_logout()));
    connect ( m_client , SIGNAL(emailAlreadyExists(bool)) , this , SLOT(on_email_exists(bool)));
    connect ( m_client , SIGNAL(nicknameAlreadyExists(bool)) , this , SLOT(on_nickname_exists(bool)));
    connect ( m_client , SIGNAL(refreshCompleted( )) , this , SLOT(on_refresh_boardgames( )));

    // Init Bgg API

    m_bgg_api = new Bgg::BggApi( Q_NULLPTR , Bgg::BGG_V2 );

    // Setup context
    m_context = rootContext();
    m_context->setContextProperty("mainWidget", this);

   setSource(QUrl("qrc:///qml/main.qml"));


}

//////////////////////////////////////////////////////////////////////////////////////////////////////
MainWidget::~MainWidget()
{
    qDebug() << "MainWidget::~MainWidget()";

    delete m_client;

    delete m_bgg_api;
}

/*
invokable for QML side
*/

void
MainWidget::Login( QString  l ,  QString p)
{
    m_client->loginJac( l , p );   

}

void
MainWidget::Logout( )
{
    m_client->logoutJac( );

}

void
MainWidget::Inscription()
{
    emit inscription();
}

void
MainWidget::CheckEmail( QString email )
{
    m_client->checkEmail( email );
}

void
MainWidget::CheckNickname( QString nickname )
{
    m_client->checkNickname( nickname );
}

void
MainWidget::CreateUser( QObject * datas)
{
    m_client->createUser( datas );
}

void
MainWidget::refreshBoardGames( )
{
    m_client->refreshBoardGames();
}

/*
private slots from JacClient
*/
void
MainWidget::on_login()
{
    emit login();
}

void
MainWidget::on_email_exists( bool result )
{    
    emit emailExists( result );
}

void
MainWidget::on_nickname_exists( bool result )
{
    emit nicknameExists( result );
}

void
MainWidget::on_logout()
{
    emit logout();
}

void
MainWidget::Search()
{
    if ( m_client->bggNickname().compare("") != 0 )
    {
        Bgg::SearchCollectionQuery * query = m_bgg_api->searchCollectionQuery( m_client->bggNickname() );

        if(query)
        {
           emit searchBegin();

           connect(query, SIGNAL(results(Bgg::SearchCollectionQuery *)), this, SLOT(on_search_collection_results(Bgg::SearchCollectionQuery *)));
        }
    }
}


void
MainWidget::on_search_collection_results(Bgg::SearchCollectionQuery * query )
{
    if(query)
    {
        if(query->hasError())
        {
            if(query->errorCode() == Bgg::StatusTooManyRequest)
             qCritical() << "<MainWidget::on_search_collection_results>: Error code=" << query->errorCode() << ", message=" << query->errorMessage();
        }
        else
        {
            SearchResult * obj = new SearchResult();
            obj->init(query);
            emit searchFetched(obj);
        }

        query->deleteLater();
    }

}

void
MainWidget::SearchBoardGames( SearchResult * result )
{
    if(!result)
        return;

    Bgg::BoardGameQuery * query = m_bgg_api->boardgameQuery(result->ids() , true );
    if(query)
       connect(query, SIGNAL(result(Bgg::BoardGameQuery *)), this, SLOT(on_boardgame_result(Bgg::BoardGameQuery *)));
}

void
MainWidget::on_boardgame_result(Bgg::BoardGameQuery * query )
{
    if(!query)
        return;

    if(query->hasError()) {
        qCritical() << "<MainWidget::on_boardgame_result>: Error code=" << query->errorCode() << ", message=" << query->errorMessage();
    }
    else {
        Bgg::MediaObjectList_sp boardgameInfoList = query->results();


        for ( int i = 0 ; i < boardgameInfoList.count() ; i++ )
        {

            Bgg::MediaObject_sp media_object =  boardgameInfoList[i];
            Bgg::BoardGameInfo_sp bg_info = qSharedPointerCast<Bgg::BoardGameInfo>(  media_object );



            Bgg::ImageQuery * iquery = m_bgg_api->imageQuery( boardgameInfoList[i] );
            if(iquery)
                connect(iquery, SIGNAL(result(Bgg::ImageQuery *)), this, SLOT(on_image_result(Bgg::ImageQuery *)));
        }
    }
    query->deleteLater();
}

void
MainWidget::on_image_result( Bgg::ImageQuery * query )
{

    if(!query)
        return;

    if(query->hasError()) {
        qCritical() << "<MainWidget::on_image_result>: Error code=" << query->errorCode() << ", message=" << query->errorMessage();
    }
    else {
        Bgg::BoardGameInfo_sp bg_info = qSharedPointerDynamicCast<Bgg::BoardGameInfo>(query->result());
        if( bg_info )
        {
            m_client->addBoardGame( bg_info );
        }
    }
    query->deleteLater();

}

void
MainWidget::on_refresh_boardgames( )
{

}
