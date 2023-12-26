LIBTARGET = chesscore
INCLUDEPATH *= $${PWD}/

LIBRARY_OUT_PWD = $$clean_path($$OUT_PWD/$$relative_path($$PWD, $$_PRO_FILE_PWD_)/debug)

LIBS += -L$${LIBRARY_OUT_PWD} -l$${LIBTARGET}

PRE_TARGETDEPS += $${LIBRARY_OUT_PWD}/lib$${LIBTARGET}.a
