#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T19:51:39
#
#-------------------------------------------------

VERSION = 0.5.1
USE_RESOURCES = 0

QT += network
CONFIG += qt thread
CONFIG += link_pkgconfig

greaterThan(QT_MAJOR_VERSION, 5) {
    QT += qml quick concurrent location widgets webkitwidgets webkit
    CONFIG += qml quick concurrent location
    #PKGCONFIG += Qt5WebKitWidgets Qt5Location Qt5Quick
}
lessThan(QT_MAJOR_VERSION, 5) {
    QT += webkit
    CONFIG += webkit mobility
    MOBILITY = location
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
    PLATFORM_HEADERS = view.h
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
    PLATFORM_HEADERS = view.h
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
symbian {
    QT += declarative
    DEFINES += TARGET_PLATFORM_SYMBIAN
    PLATFORM = symbian
    PLATFORM_SOURCES = view.cpp
    PLATFORM_HEADERS = view.h
}
!sailfish:!harmattan:!maemo5:!symbian {
    PLATFORM = desktop
    DEFINES += TARGET_PLATFORM_DESKTOP
    PLATFORM_SOURCES = view.cpp
}

message(Compiling For:    $$PLATFORM)
message(Platform Sources: $$PLATFORM_SOURCES)
message(Qt Version:       $$QT_MAJOR_VERSION $$QT_MINOR_VERSION)
message(Qt Modules Used:  $$QT)
message(Building version: $$VERSION)

TARGET = quandoparte
TEMPLATE = app
VERSION_STRING = '\\"$${VERSION}\\"'
DEFINES += QP_VERSION=\"$${VERSION_STRING}\"

contains(USE_RESOURCES,1) {
    DEFINES += USE_RESOURCES=1
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

symbian {
    TARGET.UID3 = 0xe30fb688
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

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
    resources/harmattan/qml/StationScheduleDelegate.qml

OTHER_FILES += \
    resources/harmattan/applications/quandoparte.desktop \
    resources/fremantle/applications/quandoparte.desktop \
    icons/48x48/quandoparte.png \
    icons/64x64/quandoparte.png \
    icons/80x80/quandoparte.png \
    icons/scalable/quandoparte.svg \
    icons/sailfish/90x90/quandoparte.svg \
    icons/sailfish/scalable/quandoparte.svg \
    icons/quandoparte.png \
    resources/quandoparte.css \
    resources/arrivals.css \
    resources/departures.css \
    $$replace(TRANSLATIONS, .ts, .qm) \
    resources/stations/stations.qpl \
    resources/stations/generatelist.xq \
    resources/stations/generateunclassifiedlist.xq \
    $$QMLSOURCES

unix {
    isEmpty(PREFIX) {
        maemo5 {
            PREFIX=/opt/usr
        }
        harmattan {
            PREFIX=/opt/$${TARGET}
        }
        sailfish:desktop {
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
    contains(USE_RESOURCES,1) {
        DATADIR=":"
    } else {
        DATADIR=$$PREFIX/share/apps/$${TARGET}
    }
    DEFINES += DATADIR=\\\"$${DATADIR}\\\" PKGDATADIR=\\\"$${PKGDATADIR}\\\"
}

message(Installing to prefix $$PREFIX)

unix:!symbian {
    target.path = $$BINDIR
    INSTALLS += target
}

unix:!symbian {
    desktopfile.files = resources/$$PLATFORM/applications/$${TARGET}.desktop
    desktopfile.path = $$DESKTOPDIR
    INSTALLS += desktopfile
}

unix:!symbian {
    i18n.files = $$replace(TRANSLATIONS, .ts, .qm)
    stations.files = resources/stations/stations.qpl

    i18n.path = $$DATADIR/i18n
    stations.path = $$DATADIR/stations

    icon48.files = icons/48x48/$${TARGET}.png
    icon64.files = icons/64x64/$${TARGET}.png
    iconscalable.files = icons/scalable/$${TARGET}.svg

    icon48.path = /usr/share/icons/hicolor/48x48/apps
    icon64.path = /usr/share/icons/hicolor/64x64/apps
    iconscalable.path = /usr/share/icons/hicolor/scalable/apps

    INSTALLS += icon48
    INSTALLS += iconscalable
    !contains(USE_RESOURCES,1) {
        INSTALLS += i18n
        INSTALLS += stations
    }
}

maemo5 {
    css.files = resources/$${TARGET}.css resources/arrivals.css resources/departures.css
    css.path = $$DATADIR/css
    !contains(USE_RESOURCES,1) {
        INSTALLS += css
    }
}

sailfish {
    icon90.files = icons/sailfish/90x90/$${TARGET}.png
    icon90.path = /usr/share/icons/hicolor/meegotouch/apps
    INSTALLS += icon90
}
harmattan {
    icon80.files = icons/80x80/$${TARGET}.png
    icon80.path = /usr/share/icons/hicolor/meegotouch/apps
    INSTALLS += icon80
}

!contains(USE_RESOURCES,1) {
    harmattan {
        qml.files = resources/harmattan/qml/*.qml resources/harmattan/qml/*.js
        qml.path = $$DATADIR/qml
        INSTALLS += qml
    }
}

contains(USE_RESOURCES,1) {
    RESOURCES += \
        quandoparte.qrc
}

hack_to_fix_translations {
    SOURCES += $$QMLSOURCES
}
