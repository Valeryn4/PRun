#-------------------------------------------------
#
# Project created by QtCreator 2015-10-03T17:54:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PRun
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    source/pcore.cpp \
    source/pbase.cpp

HEADERS  += mainwindow.h \
    source/pcore.h \
    source/pbase.h

FORMS    += mainwindow.ui
