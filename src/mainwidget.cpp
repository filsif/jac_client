#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QSharedPointer>

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
    m_client = new jac::JacClient( );
    connect ( m_client , SIGNAL(login()) , this , SLOT(onLogin()));
    connect ( m_client , SIGNAL(logout()) , this , SLOT(onLogout()));

    // Init Bgg API

    m_bgg_api = new Bgg::BggApi( );

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
MainWidget::onLogin()
{
    emit login();
}

void
MainWidget::onLogout()
{
    emit logout();
}

void
MainWidget::Search()
{
    Bgg::SearchCollectionQuery * query = m_bgg_api->searchCollectionQuery( "filsif");

    if(query)
    {
       emit searchBegin();

       connect(query, SIGNAL(results(Bgg::SearchCollectionQuery *)), this, SLOT(on_search_collection_results(Bgg::SearchCollectionQuery *)));
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

            qDebug() << "<MainWidget::on_search_collection_results> : " ;

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

    Bgg::BoardGameQuery * query = m_bgg_api->boardgameQuery(result->ids() );
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

            qDebug() << "game is : " << bg_info->title();

            m_client->addBoardGame( bg_info );





            /*
            Bgg::ImageQuery * iquery = m_bgg_api->imageQuery( boardgameInfoList[i] );
            if(iquery)
                connect(iquery, SIGNAL(result(Bgg::ImageQuery *)), this, SLOT(on_image_result(Bgg::ImageQuery *)));*/
        }
    }
    query->deleteLater();
}
