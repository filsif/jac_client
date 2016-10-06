#ifndef BOARDGAMEDATAMODEL_H
#define BOARDGAMEDATAMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QObject>
#include <QVector>

#include "boardgamedata.h"


/*!
 * \brief The MovieDataModel class
 */
class BoardGameDataModel
        : public QAbstractListModel
{
    Q_OBJECT

public:

    enum BoardGameRoles
    {
        TitleRole = Qt::UserRole + 1,
        VersionTitleRole,
        SynopsisRole,
        MinAgeRole,
        MinPlayerRole,
        MaxPlayerRole,
        DurationRole,
        CoverRole,
        ThumbnailRole,
        NbRole
    };

    BoardGameDataModel(QObject *parent = 0);
    ~BoardGameDataModel();


    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


public slots:
    void addBoardGame(BoardGameData *bg);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<BoardGameData *> m_boardgames;

};
#endif // BOARDGAMEDATAMODEL_H
