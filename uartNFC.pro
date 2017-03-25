#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T21:30:33
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uartNFC
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mainwindow.cpp \
    RFdeskCore/deskcore.cpp \
    RFdeskCore/DIYPack/mesmanager.cpp \
    RFdeskCore/PN532/nfcpack.cpp \
    RFdeskCore/DIYPack/diypack.cpp \
    RFdeskCore/commucore.cpp \
    RFdeskCore/usercore.cpp \
    debugwindow.cpp

HEADERS  += mainwindow.h \
    RFdeskCore/deskcore.h \
    RFdeskCore/DIYPack/mesmanager.h \
    RFdeskCore/PN532/nfcpack.h \
    RFdeskCore/DIYPack/diypack.h \
    RFdeskCore/commucore.h \
    RFdeskCore/usercore.h \
    debugwindow.h

FORMS    += mainwindow.ui \
    debugwindow.ui

DISTFILES +=
