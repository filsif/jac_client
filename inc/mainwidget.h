#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QHash>
#include <QQmlContext>
#include <QQuickView>
#include <QList>


#include "jacclient.h"
#include "libbgg/api.h"


class SearchResult
        : public QObject
{
    Q_OBJECT


public:
    SearchResult()
    {

    }

    ~SearchResult()
    {
        qDebug() << "~SearchResult() called.";

    }

    void init(Bgg::SearchQuery *query)
    {
        m_ids.clear();


        foreach(Bgg::SearchSummary_sp summary, query->results())
            m_ids << summary->id();
    }

    void init(Bgg::SearchCollectionQuery *query)
    {
        m_ids.clear();


        foreach(Bgg::SearchCollectionSummary_sp summary, query->results())
            m_ids << summary->id();
    }



    const QList<int>& ids() const
    {
        return m_ids;
    }

 signals:
    void finished();


private:
    QList<int> m_ids;
};




/*!
 *  \author Frederic MAZUR
 *  \date   23/08/2016
 *  \brief The MainWidget class
 */
class MainWidget : public QQuickView
{
    Q_OBJECT

signals:

    void    login();
    void    logout();

    void    searchBegin();
    void    searchFetched( SearchResult * result );

public:
    MainWidget(QWindow *parent = 0);
    ~MainWidget();



public slots:

    void    Login ( QString ,  QString );
    void    Logout();
    void    onLogin();
    void    onLogout();

    void    Search();
    void    SearchBoardGames( SearchResult *obj );

    void    on_search_collection_results( Bgg::SearchCollectionQuery * );
    void    on_boardgame_result(Bgg::BoardGameQuery *);
    void    on_image_result( Bgg::ImageQuery * query );

private slots:


private:
    QQmlContext *       m_context;
    jac::JacClient *    m_client;
    Bgg::BggApi *       m_bgg_api;


};




#endif // MAINWIDGET_H
