#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T16:15:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia
QT += charts

TARGET = PikaMonopoly
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
        mainwindow.cpp \
    square.cpp \
    monopoly.cpp \
    player.cpp \
    humanplayer.cpp \
    aiplayer.cpp \
    aiplayer.cpp \
    humanplayer.cpp \
    main.cpp \
    mainwindow.cpp \
    monopoly.cpp \
    player.cpp \
    square.cpp \
    aiplayer.cpp \
    humanplayer.cpp \
    main.cpp \
    mainwindow.cpp \
    monopoly.cpp \
    player.cpp \
    square.cpp \
    aiplayer.cpp \
    humanplayer.cpp \
    main.cpp \
    mainwindow.cpp \
    monopoly.cpp \
    player.cpp \
    square.cpp \
    community.cpp \
    chance.cpp

HEADERS += \
        mainwindow.h \
    square.h \
    monopoly.h \
    player.h \
    humanplayer.h \
    aiplayer.h \
    aiplayer.h \
    humanplayer.h \
    mainwindow.h \
    monopoly.h \
    player.h \
    square.h \
    aiplayer.h \
    humanplayer.h \
    mainwindow.h \
    monopoly.h \
    player.h \
    square.h \
    aiplayer.h \
    humanplayer.h \
    mainwindow.h \
    monopoly.h \
    player.h \
    square.h \
    community.h \
    chance.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    gifs.qrc


DISTFILES += \
    images/goku.jpg \
    images/goku.jpeg \
    pokemon/33.png \
    pokemon/30.jpg \
    pokemon/12.png \
    pokemon/22.png \
    pokemon/28.png \
    pokemon/33.png \
    pokemon/36.png
