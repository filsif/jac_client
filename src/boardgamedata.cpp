#include <QJsonValue>
#include <QJsonArray>
#include "boardgamedata.h"


extern QString g_cachePath;

//////////////////////////////////////////////////////////////////////////////////////////////////////
// BoardGameData
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
void
BoardGameData::setBoardGameInfo( const QJsonObject & obj )
{
    /* SYNTAX :
                            {
                                "model": "server.usergame",
                                "pk": 1,
                                "fields": {
                                    "boardgame": [{
                                        "model": "server.boardgame",
                                        "pk": 1,
                                        "fields": {
                                            "cover": "",
                                            "cover_md5" :"...",
                                            "name": "Abyss",
                                            "thumbnail": "http://127.0.0.1/snapshot_1_234390.jpg",
                                            "thumbnail" : "...",
                                            "genres": [1, 4, 6],
                                            "playing_time": 60,
                                            "bgg_id": 155987,
                                            "year": 2014,
                                            "synopsis": "The Abyss power is once again vacant, so the time has come to get your hands on the throne and its privileges. Use all of your cunning to win or buy votes in the Council. Recruit the most influential Lords and abuse their powers to take control of the most strategic territories. Finally, impose yourself as the only one able to rule the Abyssal people! Abyss is a game of development, combination and collection in which players try to take control of strategic locations in an underwater city. To achieve this, players must develop on three levels: first by collecting allies, then using them to recruit Lords of the Abyss, who will then grant access to different parts of the city. Players acquire cards through a draft of sorts, and the Lords of the Abyss acquired on those cards grant special powers to the cardholder \u2014 but once you use the cards to acquire a location, that power is shut off, so players need to time their land grabs well in order to put themselves in the best position for when the game ends. ",
                                            "min_player": 2,
                                            "min_age": 0,
                                            "max_player": 4
                                        }
                                    }],
                                    "user": 1,
                                    "owned": true,
                                    "qr_code": null,
                                    "nfc_tag": null,
                                    "explanation": false,
                                    "bg_version": [{
                                        "model": "server.boardgameversion",
                                        "pk": 1,
                                        "fields": {
                                            "cover": null,
                                            "cover_md5" : "...",
                                            "name": "French first edition",
                                            "thumbnail": null,
                                            "thumbnail_md5" : "..."
                                            "boardgame": 1,
                                            "year": 2014,
                                            "bgg_version_id": 234390,
                                            "language": "French"
                                        }
                                    }]
                                }
                            }
*/


    QJsonValue fields = obj["fields"];
    QJsonValue pk = obj["pk"];

    m_id = pk.toInt();

    QJsonObject fields_obj = fields.toObject();

    QJsonValue bg  = fields_obj["boardgame"];
    QJsonValue version = fields_obj["version"];

    if ( !bg.isNull())
    {
        QJsonArray bg_array = bg.toArray();

        QJsonValue b = bg_array[0];
        QJsonObject bg_obj = b.toObject();
        QJsonValue bg_fields = bg_obj["fields"];
        QJsonObject bg_fields_obj = bg_fields.toObject();

        m_title = bg_fields_obj["name"].toString();
        m_synopsis = bg_fields_obj["synopsis"].toString();
        m_min_age = bg_fields_obj["min_age"].toInt();
        m_min_player = bg_fields_obj["min_player"].toInt();
        m_max_player = bg_fields_obj["max_player"].toInt();
        m_duration = bg_fields_obj["playing_time"].toInt();
        m_year = bg_fields_obj["playing_time"].toInt();

        QJsonValue cover = bg_fields_obj["cover"];
        QJsonValue cover_md5 = bg_fields_obj["cover_md5"];

        if (!cover.isNull() && cover.toString().compare("") != 0 )
        {
            m_cover_remote_path = cover.toString();
            m_cover_md5 =cover_md5.toString();

            QUrl url = m_cover_remote_path;

            m_cover_local_path =  g_cachePath + "/" + url.fileName();
        }

        QJsonValue thumbnail = bg_fields_obj["thumbnail"];
        QJsonValue thumbnail_md5 = bg_fields_obj["thumbnail_md5"];

        if (!thumbnail.isNull() && thumbnail.toString().compare("") != 0)
        {
            m_thumbnail_remote_path = thumbnail.toString();
            m_thumbnail_md5 = thumbnail_md5.toString();

            QUrl url = m_thumbnail_remote_path;

            m_thumbnail_local_path =  g_cachePath + "/" + url.fileName();
        }

    }
    if (!version.isNull())
    {
        QJsonArray version_array = version.toArray();

        QJsonValue v = version_array[0];
        QJsonObject version_obj = v.toObject();
        QJsonValue version_fields = version_obj["fields"];
        QJsonObject version_fields_obj = version_fields.toObject();

        m_version_title = version_fields_obj["name"].toString();

        // overwrite if exists :

        QJsonValue cover_v = version_fields_obj["cover"];
        QJsonValue cover_md5_v = version_fields_obj["cover_md5"];

        if (!cover_v.isNull() && cover_v.toString().compare("") != 0 )
        {
            m_cover_remote_path = cover_v.toString();
            m_cover_md5 = cover_md5_v.toString();

            QUrl url = m_cover_remote_path;

            m_cover_local_path =  g_cachePath + "/" + url.fileName();
        }

        QJsonValue thumbnail_v = version_fields_obj["thumbnail"];
        QJsonValue thumbnail_md5_v = version_fields_obj["thumbnail_md5"];

        if (!thumbnail_v.isNull() && thumbnail_v.toString().compare("") != 0 )
        {
            m_thumbnail_remote_path = thumbnail_v.toString();
            m_thumbnail_md5 = thumbnail_md5_v.toString();

            QUrl url = m_thumbnail_remote_path;

            m_thumbnail_local_path =  g_cachePath + "/" + url.fileName();


        }

    }



}



