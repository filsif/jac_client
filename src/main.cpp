#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "jacclient.h"
#include "mainwidget.h"
#include "mydevice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("fmr-dev");
    app.setOrganizationDomain("fmr-dev.net");
    app.setApplicationName("Jouons à Châteauroux");


    qmlRegisterType<MyDevice>("mydevice", 1, 0, "MyDevice");

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
