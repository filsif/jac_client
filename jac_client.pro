TEMPLATE = app
TARGET = jac_client

include(../qmake_common.pri)

QT += qml quick network xml xmlpatterns

android: {
QT += androidextras
}

CONFIG += c++11

SOURCES += src/main.cpp \
    src/jacclient.cpp \
    src/loginquery.cpp \
    src/mainwidget.cpp \
    src/mydevice.cpp \
    src/logoutquery.cpp \
    src/addboardgamequery.cpp \
    src/checknicknamequery.cpp \
    src/checkemailquery.cpp \
    src/createuserquery.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

# Dependency to libbgg
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -lbgg
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -lbggd
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -llibbgg
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -llibbggd
else:unix:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -lbgg
else:unix:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -lbggd
else:android:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -lbgg
else:android:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR -lbggd


INCLUDEPATH += $$PWD/../libbgg/inc
DEPENDPATH  += $$PWD/../libbgg

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbgg.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbggd.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbgg.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbggd.lib
else:unix:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbgg.a
else:unix:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbggd.a
else:android:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbgg.a
else:android:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libbgg/lib/$$BUILD_CONFIG_DIR/libbggd.a

HEADERS += \
    inc/jacclient.h \
    inc/loginquery.h \
    inc/mainwidget.h \
    inc/mydevice.h \
    inc/logoutquery.h \
    inc/addboardgamequery.h \
    inc/checknicknamequery.h \
    inc/checkemailquery.h \
    inc/createuserquery.h

	
	INCLUDEPATH += . \
    ./inc
