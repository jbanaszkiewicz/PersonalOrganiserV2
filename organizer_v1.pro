#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T20:04:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = organizer_v1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zlota_godzina.cpp \
    typy.cpp \
    statystyki.cpp

HEADERS  += mainwindow.h \
    zlota_godzina.h \
    typy.h \
    statystyki.h

FORMS    += mainwindow.ui \
    statystyki.ui
