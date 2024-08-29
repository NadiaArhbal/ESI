QT += core
TEMPLATE = app
CONFIG -= app_bundle
CONFIG += console


include(..\..\config.pri)

SOURCES += \
        CheesPro.cpp \
        Controller.cpp \
        View.cpp \
        main.cpp

HEADERS += \
    ChessPro.h \
    Controller.h \
    View.h
