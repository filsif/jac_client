#ifndef BOARDGAMEDATA_H
#define BOARDGAMEDATA_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>


class BoardGameData
         : public QObject
{
    Q_OBJECT


    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString versionTitle READ versionTitle)
    Q_PROPERTY(QString synopsis READ synopsis)


    Q_PROPERTY(int minPlayer READ minPlayer)
    Q_PROPERTY(int minAge READ minAge)
    Q_PROPERTY(int maxPlayer READ maxPlayer)
    Q_PROPERTY(int duration READ duration)


public:
    BoardGameData()
    {
    }

    ~BoardGameData()
    {
        qDebug() << "~BoardGameData() called.";
    }

public:


    const QString& title() const
    {
        return m_title;
    }

    const QString& versionTitle() const
    {
        return m_version_title;
    }

    const QString synopsis() const
    {
        return m_synopsis;
    }

    int minPlayer() const
    {
        return m_min_player;
    }
    int minAge() const
    {
        return m_min_age;
    }

    int maxPlayer() const
    {
        return m_max_player;
    }

    int duration() const
    {
        return m_duration;
    }



    void setBoardGameInfo(const QJsonObject &  );


private:
    QString m_title;
    QString m_version_title;
    QString m_synopsis;
    int     m_min_age;
    int     m_min_player;
    int     m_max_player;
    int     m_duration;

};

#endif // BOARDGAMEDATA_H
