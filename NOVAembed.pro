#-------------------------------------------------
#
# Project created by QtCreator 2016-08-20T19:02:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NOVAembed
TEMPLATE = app


SOURCES += main.cpp\
        novaembed.cpp \
    bkf.cpp \
    P_bspf.cpp \
    tools.cpp \
    U_bspf.cpp \
    welcome.cpp

HEADERS  += novaembed.h

FORMS    += novaembed.ui

RESOURCES += \
    novaembedresources.qrc
