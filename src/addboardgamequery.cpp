#include "addboardgamequery.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include "jacclient.h"
#include <QTextDocument>

#include <QPixmap>

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QByteArray>
#include <QBuffer>



namespace jac
{
AddBoardGameQuery::AddBoardGameQuery( JacClient & jac , Bgg::BoardGameInfo_sp bg_infos):
m_client(jac)
,m_bg_infos(bg_infos)
,m_reply(Q_NULLPTR)
{

    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QUrl url = m_client.baseUrl();
    QString str = QString("boardgame/add/");
    url = url.resolved( str );
/*
    QUrlQuery params;

    params.addQueryItem("name"          , m_bg_infos->title());
    params.addQueryItem("year"          , QString("%1").arg(m_bg_infos->year().year()));
    params.addQueryItem("synopsis"      ,m_bg_infos->synopsis());
    params.addQueryItem("min_age"       , QString("%1").arg(m_bg_infos->minAge()));
    params.addQueryItem("min_player"    , QString("%1").arg(m_bg_infos->minPlayer()));
    params.addQueryItem("max_player"    , QString("%1").arg(m_bg_infos->maxPlayer()));
    params.addQueryItem("playing_time"  , QString("%1").arg(m_bg_infos->duration()));
    params.addQueryItem("bgg_id"        , QString("%1").arg(m_bg_infos->boardgameId()));

    const QList<QString> &genres = m_bg_infos->genres();

    for ( int i = 0 ; i < genres.length() ; i++ )
    {
        params.addQueryItem("genre"        , genres[i] );

    }
*/

    QPixmap pm_cover = m_bg_infos->cover( );
    if(!pm_cover.isNull())
    {
        QByteArray bArray;
        QBuffer buffer(&bArray);
        buffer.open(QIODevice::WriteOnly);
        pm_cover.save(&buffer, "JPG");
        QHttpPart cover_part;
        cover_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        cover_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"cover\"; filename=\"cover.jpg\""));
        cover_part.setBody( bArray);
        multipart->append(cover_part);
    }

    QPixmap pm_thumbnail = m_bg_infos->thumbnail( );
    if(!pm_thumbnail.isNull())
    {
        QByteArray bArray;
        QBuffer buffer(&bArray);
        buffer.open(QIODevice::WriteOnly);
        pm_thumbnail.save(&buffer, "JPG");
        QHttpPart thumbnail_part;
        thumbnail_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        thumbnail_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"thumbnail\"; filename=\"thumbnail.jpg\""));
        thumbnail_part.setBody( bArray);
        multipart->append(thumbnail_part);
    }

    QHttpPart data_part_name;
    data_part_name.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    data_part_name.setBody( m_bg_infos->title().toUtf8());
    multipart->append( data_part_name );

    QHttpPart data_part_year;
    data_part_year.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"year\""));
    data_part_year.setBody( QString("%1").arg(m_bg_infos->year().year()).toUtf8());
    multipart->append( data_part_year );

    QHttpPart data_part_synopsis;
    data_part_synopsis.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"synopsis\""));
    data_part_synopsis.setBody( m_bg_infos->synopsis().toUtf8());
    multipart->append( data_part_synopsis );

    QHttpPart data_part_min_age;
    data_part_min_age.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"min_age\""));
    data_part_min_age.setBody( QString("%1").arg(m_bg_infos->minAge()).toUtf8());
    multipart->append( data_part_min_age );

    QHttpPart data_part_min_player;
    data_part_min_player.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"min_player\""));
    data_part_min_player.setBody( QString("%1").arg(m_bg_infos->minPlayer()).toUtf8());
    multipart->append( data_part_min_player );

    QHttpPart data_part_max_player;
    data_part_max_player.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"max_player\""));
    data_part_max_player.setBody( QString("%1").arg(m_bg_infos->maxPlayer()).toUtf8());
    multipart->append( data_part_max_player );

    QHttpPart data_part_playing_time;
    data_part_playing_time.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"playing_time\""));
    data_part_playing_time.setBody( QString("%1").arg(m_bg_infos->duration()).toUtf8());
    multipart->append( data_part_playing_time );

    QHttpPart data_part_bgg_id;
    data_part_bgg_id.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"bgg_id\""));
    data_part_bgg_id.setBody( QString("%1").arg(m_bg_infos->boardgameId()).toUtf8());
    multipart->append( data_part_bgg_id );

    const QList<QString> &genres = m_bg_infos->genres();

    for ( int i = 0 ; i < genres.length() ; i++ )
    {
        QHttpPart data_part_genre;
        data_part_genre.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"genre\""));
        data_part_genre.setBody( genres[i].toUtf8());
        multipart->append( data_part_genre );
    }

    // ajouter les versions

    const Bgg::VersionInfoList_sp & versions = m_bg_infos->versions();
    foreach( Bgg::VersionInfo_sp version , versions)
    {
        QPixmap pm_cover_v = version->cover( );
        if(!pm_cover_v.isNull())
        {
            QByteArray bArray;
            QBuffer buffer(&bArray);
            buffer.open(QIODevice::WriteOnly);
            pm_cover_v.save(&buffer, "JPG");
            QHttpPart cover_part;
            cover_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
            cover_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"cover_%1\"; filename=\"cover_%2.jpg\"").arg( version->versionId(),version->versionId())));
            cover_part.setBody( bArray);
            multipart->append(cover_part);
        }

        QPixmap pm_thumbnail_v = version->thumbnail( );
        if(!pm_thumbnail_v.isNull())
        {
            QByteArray bArray;
            QBuffer buffer(&bArray);
            buffer.open(QIODevice::WriteOnly);
            pm_thumbnail_v.save(&buffer, "JPG");
            QHttpPart thumbnail_part;
            thumbnail_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
            thumbnail_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"thumbnail_%1\"; filename=\"thumbnail_%2.jpg\"").arg(version->versionId() , version->versionId())));
            thumbnail_part.setBody( bArray);
            multipart->append(thumbnail_part);
        }

    }

    QNetworkRequest request;
    request.setUrl(url);
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_reply = jac.postReply( request , multipart );
    multipart->setParent(m_reply); // delete the multipart with the reply
    connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_add_boardgame_finished()));

}

AddBoardGameQuery::~AddBoardGameQuery()
{

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

    }

    emit results( this );

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
