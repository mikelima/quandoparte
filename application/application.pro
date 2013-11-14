#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T19:51:39
#
#-------------------------------------------------

VERSION = 0.6.2
USE_RESOURCES = 0

QT += network
CONFIG += qt
CONFIG += link_pkgconfig

lessThan(QT_MAJOR_VERSION, 5) {
    QT += webkit
    CONFIG += webkit mobility
    MOBILITY = location
} else {
    QT += qml quick concurrent location webkitwidgets webkit
}

contains(MEEGO_EDITION, harmattan) {
   CONFIG += harmattan
}

sailfish {
    PLATFORM = sailfish
    DEFINES += TARGET_PLATFORM_SAILFISH
    # enable booster
packagesExist(qdeclarative-boostable) {
    message("Building with qdeclarative-boostable support")
    DEFINES += HAS_BOOSTER
    PKGCONFIG += qdeclarative-boostable
} else {
    warning("qdeclarative-boostable not available; startup times will be slower")
}
    QMAKE_LFLAGS += -pie -rdynamic
    PLATFORM_SOURCES = view.cpp
    PLATFORM_HEADERS = view.h view_qt5.h
}
harmattan {
    QT += declarative
    PLATFORM = harmattan
    DEFINES += TARGET_PLATFORM_HARMATTAN
    # enable booster
    CONFIG += qdeclarative-boostable
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden -Wno-psabi
    QMAKE_LFLAGS += -pie -rdynamic
    PLATFORM_SOURCES = view.cpp
    PLATFORM_HEADERS = view.h view_qt4.h
}
maemo5 {
    QT += maemo5
    PLATFORM = fremantle
    DEFINES += TARGET_PLATFORM_FREMANTLE
    PLATFORM_SOURCES = \
        app.cpp \
        stationlistview.cpp \
        stationview.cpp \
        settingsdialog.cpp \
        keypressforwarder.cpp
    PLATFORM_HEADERS= \
        app.h \
        stationlistview.h \
        keypressforwarder.h \
        settingsdialog.h \
        stationview.h
}
!sailfish:!harmattan:!maemo5 {
    PLATFORM = desktop
    DEFINES += TARGET_PLATFORM_DESKTOP
    PLATFORM_SOURCES = view.cpp
}

message(Compiling For:    $$PLATFORM)
message(Platform Sources: $$PLATFORM_SOURCES)
message(Qt Version:       $$QT_MAJOR_VERSION"."$$QT_MINOR_VERSION)
message(Qt Modules Used:  $$QT)
message(Building version: $$VERSION)

TARGET = quandoparte
TEMPLATE = app
VERSION_STRING = '\\"$${VERSION}\\"'
DEFINES += QP_VERSION=\"$${VERSION_STRING}\"

contains(USE_RESOURCES, 1) {
    DEFINES += USE_RESOURCES=1
    CONFIG += resources
}

!debug {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

TRANSLATIONS = resources/i18n/quandoparte_it.ts

SOURCES += \
    $$PLATFORM_SOURCES \
    main.cpp \
    stationlistmodel.cpp \
    stationlistproxymodel.cpp \
    settings.cpp \
    dataprovider.cpp \
    stationschedulemodel.cpp \
    stationscheduleitem.cpp

HEADERS += \
    $$PLATFORM_HEADERS \
    stationlistmodel.h \
    stationlistproxymodel.h \
    settings.h \
    dataprovider.h \
    stationschedulemodel.h \
    stationscheduleitem.h

FORMS += \
    settingsdialog.ui \
    stationlistview.ui

QMLSOURCES = \
    resources/harmattan/qml/main.qml \
    resources/harmattan/qml/StationListPage.qml \
    resources/harmattan/qml/StationPage.qml \
    resources/harmattan/qml/SearchBar.qml \
    resources/harmattan/qml/PageHeader.qml \
    resources/harmattan/qml/PageHeader.js \
    resources/harmattan/qml/uiconstants.js \
    resources/harmattan/qml/StationListPage.js \
    resources/harmattan/qml/AboutPage.qml \
    resources/harmattan/qml/InfoBar.qml \
    resources/harmattan/qml/DroppedShadow.qml \
    resources/harmattan/qml/DelayIndicator.qml \
    resources/harmattan/qml/StationScheduleDelegate.qml \
    resources/sailfish/qml/main.qml \
    resources/sailfish/qml/pages/AboutPage.qml \
    resources/sailfish/qml/pages/StationListPage.qml \
    resources/sailfish/qml/pages/StationPage.qml \
    resources/sailfish/qml/pages/components/DelayIndicator.qml \
    resources/sailfish/qml/pages/components/StationScheduleDelegate.qml

OTHER_FILES += \
    resources/sailfish/applications/quandoparte.desktop \
    resources/harmattan/applications/quandoparte.desktop \
    resources/fremantle/applications/quandoparte.desktop \
    icons/48x48/quandoparte.png \
    icons/64x64/quandoparte.png \
    icons/80x80/quandoparte.png \
    icons/scalable/quandoparte.svg \
    icons/sailfish/86x86/quandoparte.png \
    icons/sailfish/90x90/quandoparte.png \
    icons/sailfish/scalable/quandoparte.svg \
    icons/quandoparte.png \
    resources/quandoparte.css \
    resources/arrivals.css \
    resources/departures.css \
    $$replace(TRANSLATIONS, .ts, .qm) \
    resources/stations/stations.qpl \
    resources/stations/generatelist.xq \
    resources/stations/generateunclassifiedlist.xq \
    $$QMLSOURCES \
    resources/sailfish/qml/StationListPage.qml

isEmpty(PREFIX) {
    maemo5 {
        PREFIX=/opt/usr
    }
    harmattan {
        PREFIX=/opt/$${TARGET}
    }
    sailfish {
        PREFIX=/usr
    }
    !maemo5:!harmattan:!sailfish {
        PREFIX=/usr/local
    }
}
maemo5 {
    DESKTOPDIR=/usr/share/applications/hildon
}
harmattan {
    DESKTOPDIR=/usr/share/applications
}
sailfish {
    DESKTOPDIR=$$PREFIX/share/applications
}
desktop {
    DESKTOPDIR=$$PREFIX/share/applications
}
BINDIR=$$PREFIX/bin
contains(USE_RESOURCES, 1) {
    DATADIR=":"
} else {
    DATADIR=$$PREFIX/share/apps/$${TARGET}
}
DEFINES += DATADIR=\\\"$${DATADIR}\\\" PKGDATADIR=\\\"$${PKGDATADIR}\\\"

message(Installing to prefix $$PREFIX)
message(Executable to $$BINDIR)
message(Desktop file to $$DESKTOPDIR)
message(Data to $$DATADIR)
message(Extra defines $$DEFINES)

target.path = $$BINDIR
INSTALLS += target

unix:sailfish {
    desktopfile.files = resources/$$PLATFORM/applications/$${TARGET}.desktop
    desktopfile.path = $$DESKTOPDIR
    INSTALLS += desktopfile
}

unix:sailfish {
    i18n.files = $$replace(TRANSLATIONS, .ts, .qm)
    stations.files = resources/stations/stations.qpl

    i18n.path = $$DATADIR/i18n
    stations.path = $$DATADIR/stations

    INSTALLS += i18n
    INSTALLS += stations
}

desktop {
    icon48.files = icons/48x48/$${TARGET}.png
    icon64.files = icons/64x64/$${TARGET}.png
    iconscalable.files = icons/scalable/$${TARGET}.svg

    icon48.path = /usr/share/icons/hicolor/48x48/apps
    icon64.path = /usr/share/icons/hicolor/64x64/apps
    iconscalable.path = /usr/share/icons/hicolor/scalable/apps

    INSTALLS += icon48
    INSTALLS += iconscalable
}

maemo5 {
    css.files = resources/$${TARGET}.css resources/arrivals.css resources/departures.css
    css.path = $$DATADIR/css
    !contains(USE_RESOURCES, 1) {
        INSTALLS += css
    }
}

sailfish {
    icon86.files = icons/sailfish/86x86/$${TARGET}.png
    icon86.path = /usr/share/icons/hicolor/meegotouch/apps
    INSTALLS += icon86
}

harmattan {
    desktopfile.files = resources/$$PLATFORM/applications/$${TARGET}.desktop
    desktopfile.path = $$DESKTOPDIR
    INSTALLS += desktopfile

    icon48.files = icons/48x48/$${TARGET}.png
    icon48.path = /usr/share/icons/hicolor/48x48/apps
    INSTALLS += icon48

    icon64.files = icons/64x64/$${TARGET}.png
    icon64.path = /usr/share/icons/hicolor/64x64/apps
    INSTALLS += icon64

    iconscalable.files = icons/scalable/$${TARGET}.svg
    iconscalable.path = /usr/share/icons/hicolor/scalable/apps
    INSTALLS += iconscalable

    INSTALLS += i18n
    INSTALLS += stations
    icon80.files = icons/80x80/$${TARGET}.png
    icon80.path = /usr/share/icons/hicolor/meegotouch/apps
    INSTALLS += icon80

    i18n.files = $$replace(TRANSLATIONS, .ts, .qm)
    i18n.path = $$DATADIR/i18n
    INSTALLS += i18n

    stations.files = resources/stations/stations.qpl
    stations.path = $$DATADIR/stations
    INSTALLS += stations
}

!contains(USE_RESOURCES, 1) {
    sailfish {
        qml.files = resources/sailfish/qml/*.qml \
                    resources/sailfish/qml/*.js \
                    resources/sailfish/qml/pages \
                    resources/sailfish/qml/pages/components \
                    resources/sailfish/qml/cover
        qml.path = $$DATADIR/qml
        INSTALLS += qml
    }
    harmattan {
        qml.files = resources/harmattan/qml/*.qml resources/harmattan/qml/*.js
        qml.path = $$DATADIR/qml
        INSTALLS += qml
    }
}

contains(USE_RESOURCES, 1) {
    RESOURCES += \
        quandoparte.qrc
}

hack_to_fix_translations {
    SOURCES += $$QMLSOURCES
}
