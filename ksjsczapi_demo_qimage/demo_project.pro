#-------------------------------------------------
#
# Project created by QtCreator 2018-06-19T10:45:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = ksjsczapi_demo_qimage
TEMPLATE = app
DEFINES -= _UNICODE
LIBS     = -L../ksjsczapi_lib -lksjscz

DESTDIR   = ../ksjsczapi_demo_bin

SOURCES += main.cpp \ 
    KSJSCZDemoMainWindow.cpp \
    KSJVBImageZoom.cpp

HEADERS  += \
    KSJVBImageZoom.h \
    KSJSCZDemoMainWindow.h

FORMS    += \
    KSJSCZDemoMainWindow.ui



