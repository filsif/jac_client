#include "addboardgamequery.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include "jacclient.h"


namespace jac
{
AddBoardGameQuery::AddBoardGameQuery( JacClient & jac , Bgg::BoardGameInfo_sp bg_infos):
m_client(jac)
,m_bg_infos(bg_infos)
,m_reply(Q_NULLPTR)
{

    QUrl url = m_client.baseUrl();
    QString str = QString("boardgame/add/");
    url = url.resolved( str );

    QUrlQuery params;

    params.addQueryItem("name"          , m_bg_infos->title());
    params.addQueryItem("year"          , QString("%1").arg(m_bg_infos->year().year()));
    params.addQueryItem("synopsis"      , m_bg_infos->synopsis());
    params.addQueryItem("min_age"       , QString("%1").arg(m_bg_infos->minAge()));
    params.addQueryItem("min_player"    , QString("%1").arg(m_bg_infos->minPlayer()));
    params.addQueryItem("max_player"    , QString("%1").arg(m_bg_infos->maxPlayer()));
    params.addQueryItem("playing_time"  , QString("%1").arg(m_bg_infos->duration()));
    params.addQueryItem("bgg_id"        , QString("%1").arg(m_bg_infos->boardgameId()));

    //url.setQuery(params);

    qDebug() << "Start AddBoardgame Query on : " << url.toString();
    qDebug() << "Query Params  : " << params.toString();
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_reply = jac.postReply( request , params );
    connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_add_boardgame_finished()));

}

AddBoardGameQuery::~AddBoardGameQuery()
{
    qDebug() << "Destroy Add BoardGame Query";

}


void
AddBoardGameQuery::on_add_boardgame_finished()
{




    if (m_reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Network error. Error code is : " << m_reply->error();
    }
    else
    {
        qDebug()<< "REPLY " << m_reply->readAll();
    }

    emit results( this );

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
