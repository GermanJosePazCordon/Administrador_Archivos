QT += core
QT -= gui

CONFIG += c++11

TARGET = P1MIA
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    obmkdisk.cpp \
    parser.cpp \
    scanner.cpp \
    obrmdisk.cpp \
    obfdisk.cpp \
    obmount.cpp \
    obumount.cpp \
    obmkfs.cpp \
    obtouch.cpp \
    obmkdir.cpp \
    obreporte.cpp \
    obcat.cpp \
    obren.cpp \
    obrm.cpp \
    obedit.cpp \
    obexec.cpp \
    obmv.cpp \
    obcp.cpp \
    obfind.cpp \
    oblogin.cpp \
    oblogout.cpp \
    obmkgrp.cpp \
    obrmgrp.cpp \
    obmkusr.cpp \
    obrmusr.cpp \
    obchgrp.cpp \
    obloss.cpp \
    obrecovery.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    lexico.l \
    parser.y \
    comandos

HEADERS += \
    obmkdisk.h \
    parser.h \
    scanner.h \
    structs.h \
    obrmdisk.h \
    obfdisk.h \
    obmount.h \
    obumount.h \
    obmkfs.h \
    obtouch.h \
    obmkdir.h \
    obreporte.h \
    obcat.h \
    obren.h \
    obrm.h \
    obedit.h \
    obexec.h \
    obmv.h \
    obcp.h \
    obfind.h \
    oblogin.h \
    oblogout.h \
    obmkgrp.h \
    obrmgrp.h \
    obmkusr.h \
    obrmusr.h \
    obchgrp.h \
    obloss.h \
    obrecovery.h

SUBDIRS += \
    P1MIA.pro
