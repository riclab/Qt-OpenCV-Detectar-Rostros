#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T19:14:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DetectarRostros-OpenCV
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv-3.1.0
LIBS += `pkg-config opencv --libs --cflags`

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
