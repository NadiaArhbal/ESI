QT -= qt

TEMPLATE = lib
include(../../config.pri)

CONFIG += $${CORELIBMODE}



SOURCES += \
    Position.cpp \
    board.cpp \
    game.cpp \
    pieces.cpp \
    observer/subject.cpp

HEADERS += \
    PieceType.h \
    Position.h \
    Side.h \
    board.h \
    chesscore.h \
    game.h \
    pieces.h \
    observer/observer.h \
    observer/subject.h

DISTFILES += \
    chesscore.pri

