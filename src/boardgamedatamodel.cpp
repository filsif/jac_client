#include "inc/boardgamedatamodel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
// BoardGameDataModel
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
BoardGameDataModel::BoardGameDataModel(QObject *parent)
 : QAbstractListModel(parent)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
BoardGameDataModel::~BoardGameDataModel()
{
    clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void
BoardGameDataModel::addBoardGame(BoardGameData *bg)
{
    if(bg){
        int idx = m_boardgames.indexOf(bg);
        if(idx != -1) {
            emit dataChanged(createIndex(idx, 0), createIndex(idx, NbRole-1));
        }
        else {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_boardgames << bg;
            endInsertRows();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void
BoardGameDataModel::clear()
{
    // Super important de prévenir qu'on va supprimer
    // sinon la ListView dans QML ne sera pas notifiée et...CRASH
    beginRemoveRows(QModelIndex(), 0, rowCount());
    qDeleteAll(m_boardgames);
    m_boardgames.clear();
    endRemoveRows();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int
BoardGameDataModel::rowCount(const QModelIndex & parent /*= QModelIndex()*/) const
{
    Q_UNUSED(parent)
    return m_boardgames.count();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant
BoardGameDataModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole*/) const
{
    if (index.row() < 0 || index.row() >= m_boardgames.count())
        return QVariant();

    const BoardGameData *bg = m_boardgames[index.row()];
    switch(role){
    case TitleRole:
        return bg->title();
    case VersionTitleRole:
        return bg->versionTitle();
    case SynopsisRole:
        return bg->synopsis();
    case MinAgeRole:
        return bg->minAge();
    case MinPlayerRole:
        return bg->minPlayer();
    case MaxPlayerRole :
        return bg->maxPlayer();
    case DurationRole :
        return bg->duration();
    case CoverRole :
        return bg->cover();
    case ThumbnailRole :
        return bg->thumbnail();
    default:
        break;
    }

    return QVariant();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
QHash<int, QByteArray>
BoardGameDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[VersionTitleRole] = "version title";
    roles[SynopsisRole] = "synopsis";
    roles[MinAgeRole] = "min age";
    roles[MinPlayerRole] = "min player";
    roles[MaxPlayerRole] = "max player";
    roles[DurationRole] = "duration";
    roles[CoverRole] = "cover";
    roles[ThumbnailRole] = "thumbnail";
    return roles;

}
