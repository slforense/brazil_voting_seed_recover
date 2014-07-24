#-------------------------------------------------
#
# Project created by QtCreator 2014-07-14T10:29:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vote
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    candidate.cpp \
    role.cpp

HEADERS  += mainwindow.h \
    candidate.h \
    role.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES +=
