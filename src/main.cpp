#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QDir>


#include "jacclient.h"
#include "mainwidget.h"
#include "mydevice.h"
#include "boardgamedata.h"
#include "boardgamedatamodel.h"


QString g_cachePath;


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("fmr-dev");
    app.setOrganizationDomain("fmr-dev.net");
    app.setApplicationName("Jouons à Châteauroux");

    g_cachePath = QStandardPaths::writableLocation( QStandardPaths::CacheLocation );
    QDir dir(g_cachePath);
    if ( !dir.exists())
    {
        dir.mkpath(g_cachePath);
    }

    qDebug() << "standard path for cache is : " << g_cachePath;


    qmlRegisterType<MyDevice>("mydevice", 1, 0, "MyDevice");
    qmlRegisterType<BoardGameData>("fr.jac.client", 1,0,"BoardGameData");
    qmlRegisterType<BoardGameDataModel>("fr.jac.client", 1,0,"BoardGameDataModel");



/*
 *

    jac::JacClient c;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));*/

    MainWidget mainWidget;
    mainWidget.show();


    int ret = app.exec();

    return ret;
}
