#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T12:22:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kanade2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp
SOURCES += kanade.cpp

HEADERS  += mainwindow.h \
    presets.h
HEADERS  += kanade.h

FORMS    += mainwindow.ui

include(Qt-Color-Picker-master/color_widgets.pri)
