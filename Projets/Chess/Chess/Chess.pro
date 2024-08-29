TEMPLATE = subdirs

SUBDIRS += \
    src/chess_server \
    src/chesscore \
    src/gui \
    src/test \
    src/tui
src-tui.depends += src/chesscore
src-gui.depends += src/chesscore
src-test.depends += src/chesscore

OTHER_FILES += config.pri \
