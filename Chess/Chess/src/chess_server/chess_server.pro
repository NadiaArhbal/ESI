QT += core
QT += network
QT += sql
TEMPLATE = app
CONFIG -= app_bundle
CONFIG += console

include(../../config.pri)
SOURCES += \
        ChessServer.cpp \
        business/AdminModel.cpp \
        db/GameDB.cpp \
        db/PlayerDB.cpp \
        db/PlayerStatDB.cpp \
        db/SequenceDB.cpp \
        main.cpp

HEADERS += \
    ChessServer.h \
    MessageType.h \
    ServerView.h \
    business/AdminFacade.h \
    business/AdminModel.h \
    business/GameBusinessLogic.h \
    business/PlayerBusinessLogic.h \
    db/DBManager.h \
    db/GameDB.h \
    db/PlayerDB.h \
    db/SequenceDB.h \
    dto/EntityDto.h \
    dto/GameDto.h \
    dto/PlayerDto.h \
    specification/GameSpecification.h \
    specification/PlayerSpecification.h
