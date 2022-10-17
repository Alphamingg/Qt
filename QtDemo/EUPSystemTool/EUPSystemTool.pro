#-------------------------------------------------
#
# Project created by QtCreator 2022-06-21T15:41:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EUPSystemTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    appmodule.cpp \
    checklibmodule.cpp \
    devicemodule.cpp \
    diskmodule.cpp \
    gpumodule.cpp \
        main.cpp \
    memmodule.cpp \
    osinfomodule.cpp \
        outline.cpp \
    errnomodule.cpp \
    cpumodule.cpp \
    publicfunc.cpp

HEADERS += \
    appmodule.h \
    checklibmodule.h \
    devicemodule.h \
    diskmodule.h \
    gpumodule.h \
    memmodule.h \
    osinfomodule.h \
        outline.h \
    errnomodule.h \
    cpumodule.h \
    publicfunc.h

FORMS +=

RESOURCES += \
    res.qrc

DISTFILES += \
    README.md
