#-------------------------------------------------
#
# Project created by QtCreator 2011-05-08T17:25:28
#
#-------------------------------------------------

QT       += network webkit xml testlib

TARGET = tst_quandopartetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_app.cpp ../application/stationlistmodel.cpp

HEADERS += ../application/stationlistmodel.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/bin
    } else {
        target.path = /usr/local/bin
    }
    INSTALLS += target
}

OTHER_FILES += \
    testfiles/empty.qpl \
    testfiles/malformed1.qpl \
    testfiles/emptystation.qpl \
    testfiles/teststation.qpl
