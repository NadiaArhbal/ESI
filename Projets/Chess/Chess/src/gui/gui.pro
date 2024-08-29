QT += core gui network
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../config.pri)

DEFINES += QT_DEPRECATED_WARNINGS


HEADERS += \
    boardview.h \
    landingchipitem.h \
    chessview.h \
    eatenpieces.h \
    history.h \
    paramstock.h \
    pieceitem.h \
    playerinfo.h \
    point.h \
    newaccount.h \
    playerconnection.h \
    promotion.h

SOURCES += \
        boardview.cpp \
        chessview.cpp \
        eatenpieces.cpp \
        history.cpp \
        landingchipitem.cpp \
        main.cpp \
        paramstock.cpp \
        pieceitem.cpp \
        playerinfo.cpp \
        point.cpp \
        newaccount.cpp \
        playerconnection.cpp \
        promotion.cpp


FORMS += \
    chessview.ui \
    newaccount.ui \
    paramstock.ui \
    playerconnection.ui \
    promotion.ui

RESOURCES += ../../resources/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
