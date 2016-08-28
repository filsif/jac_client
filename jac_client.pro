TEMPLATE = app
TARGET = jac_client

include(../qmake_common.pri)

QT += qml quick network

android: {
QT += androidextras
}

CONFIG += c++11

SOURCES += src/main.cpp \
    src/jacclient.cpp \
    src/loginquery.cpp \
    src/mainwidget.cpp \
    src/mydevice.cpp \
    src/logoutquery.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    inc/jacclient.h \
    inc/loginquery.h \
    inc/mainwidget.h \
    inc/mydevice.h \
    inc/logoutquery.h

	
	INCLUDEPATH += . \
    ./inc
