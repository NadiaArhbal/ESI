TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
QMAKE_CXXFLAGS += -O3

include(..\..\config.pri)

SOURCES += \
    main.cpp \
    tst_model.cpp

