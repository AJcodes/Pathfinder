#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T18:02:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pathfinder
TEMPLATE = app
CONFIG += static

SOURCES += main.cpp \
    game.cpp \
    block.cpp \
    window.cpp

HEADERS  += \
    game.h \
    block.h \
    window.h

FORMS    +=

DISTFILES += \
    maze1.png \
    maze2.png \
    maze3.png \
    maze4.png \
    maze5.png

RESOURCES += \
    images.qrc
