#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T19:51:39
#
#-------------------------------------------------

CONFIG += qt webkit mobility
QT += webkit network maemo5
MOBILITY = location

TARGET = quandoparte
TEMPLATE = app
VERSION = 0.3.5
VERSION_STRING = '\\"$${VERSION}\\"'
DEFINES += QP_VERSION=\"$${VERSION_STRING}\"

TRANSLATIONS = resources/i18n/quandoparte_it.ts

SOURCES += main.cpp \
    settingsdialog.cpp \
    stationview.cpp \
    app.cpp \
    stationlistview.cpp \
    keypressforwarder.cpp \
    stationlistmodel.cpp \
    stationlistproxymodel.cpp

HEADERS += \
    settingsdialog.h \
    stationview.h \
    app.h \
    stationlistview.h \
    keypressforwarder.h \
    stationlistmodel.h \
    stationlistproxymodel.h

FORMS += \
    settingsdialog.ui \
    stationlistview.ui

symbian {
    TARGET.UID3 = 0xe30fb688
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

OTHER_FILES += \
    quandoparte.desktop \
    icons/quandoparte.png \
    resources/quandoparte.css \
    resources/arrivals.css \
    resources/departures.css \
    $$replace(TRANSLATIONS, .ts, .qm) \
    resources/stations/stations.qpl

message($${OTHER_FILES})

unix {
    isEmpty(PREFIX) {
        maemo5 {
            PREFIX=/opt/usr
        } else {
            PREFIX=/usr/local
        }
    }
    BINDIR=$$PREFIX/bin
    DATADIR=$$PREFIX/share/apps/$${TARGET}
    DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"
}


unix:!symbian {
    target.path = $$BINDIR
    INSTALLS += target
}

unix:!symbian {
    desktopfile.files = $${TARGET}.desktop
    maemo5 {
        desktopfile.path = /usr/share/applications/hildon
    } else {
        desktopfile.path = $$DATADIR/applications
    }
    INSTALLS += desktopfile
}

unix:!symbian {
    css.files = resources/$${TARGET}.css resources/arrivals.css resources/departures.css
    i18n.files = $$replace(TRANSLATIONS, .ts, .qm)
    stations.files = resources/stations/stations.qpl

    i18n.path = $$DATADIR/i18n
    css.path = $$DATADIR/css
    stations.path = $$DATADIR/stations

    icon48.files = icons/48x48/$${TARGET}.png
    icon64.files = icons/64x64/$${TARGET}.png

    icon48.path = /usr/share/icons/hicolor/48x48/apps
    icon64.path = /usr/share/icons/hicolor/64x64/apps

    INSTALLS += icon48
    INSTALLS += icon64
    INSTALLS += css
    INSTALLS += i18n
    INSTALLS += stations
}

unix {
    desktopfile.files = $${TARGET}.desktop
    maemo5 {
        desktopfile.path = /usr/share/applications/hildon
    } else {
        desktopfile.path = $$DATADIR/applications
    }
    INSTALLS += desktopfile
}
