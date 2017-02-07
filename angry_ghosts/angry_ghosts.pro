#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T21:08:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Angry Ghosts"
TEMPLATE = app


SOURCES += main.cpp \
    map.cpp \
    game.cpp \
    player.cpp \
    crate.cpp \
    bomb.cpp \
    explosion.cpp \
    bonus.cpp \
    enemy.cpp

HEADERS  += \
    map.h \
    game.h \
    player.h \
    crate.h \
    bomb.h \
    explosion.h \
    bonus.h \
    enemy.h

FORMS    +=

RESOURCES += \
    resources.qrc

CONFIG += c++11
