CONFIG += c++17

CONFIG += debug_and_release debug_and_release_target

INCLUDEPATH += $${PWD}/libs/

CORELIBMODE=staticlib
!equals(TARGET, chesscore) {
    include($${PWD}/src/chesscore/chesscore.pri)
}

lessThan(QT_MAJOR_VERSION, 5) {
    error("Use Qt 5 or newer")
}

lessThan(QT_MINOR_VERSION, 12) {
    # Support for c++17 CONFIG option was added in Qt 5.12
    # Fall back on compiler option for older versions.
    QMAKE_CXXFLAGS += -std=c++17
}

QMAKE_CXXFLAGS += -Wall
