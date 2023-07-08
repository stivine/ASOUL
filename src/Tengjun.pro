#-------------------------------------------------
#
# Project created by QtCreator 2023-05-13T19:45:02
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tengjun
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    mainscene.cpp \
    myrole.cpp \
    bullet.cpp \
    acao.cpp \
    gameobject.cpp \
    gameobjectpool.cpp \
    acao_follow.cpp \
    info.cpp \
    obstacle.cpp \
    drops.cpp


HEADERS += \
        widget.h \
    mainscene.h \
    myrole.h \
    bullet.h \
    acao.h \
    gameobject.h \
    gameobjectpool.h \
    acao_follow.h \
    info.h \
    obstacle.h \
    drops.h


FORMS += \
    widget.ui \
    info.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
