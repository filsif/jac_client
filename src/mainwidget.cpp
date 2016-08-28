#include <QDebug>
#include <QGuiApplication>
#include <QTimer>

#include "mainwidget.h"




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

