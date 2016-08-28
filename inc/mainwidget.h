#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QHash>
#include <QQmlContext>
#include <QQuickView>


#include "jacclient.h"




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

public:
    MainWidget(QWindow *parent = 0);
    ~MainWidget();



public slots:

    void    Login ( QString ,  QString );
    void    Logout();
    void    onLogin();
    void    onLogout();

private slots:


private:
    QQmlContext *       m_context;
    jac::JacClient *    m_client;


};

#endif // MAINWIDGET_H
