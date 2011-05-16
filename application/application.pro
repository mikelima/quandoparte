#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T19:51:39
#
#-------------------------------------------------

QT += webkit network xml maemo5

TARGET = quandoparte
TEMPLATE = app

TRANSLATIONS = resources/i18n/quandoparte_it.ts

SOURCES += main.cpp \
    settingsdialog.cpp \
    stationview.cpp \
    app.cpp \
    stationlistview.cpp

HEADERS += \
    settingsdialog.h \
    stationview.h \
    app.h \
    stationlistview.h

FORMS += \
    settingsdialog.ui \
    stationlistview.ui

CONFIG += webkit mobility
MOBILITY = location

symbian {
    TARGET.UID3 = 0xe30fb688
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

OTHER_FILES += \
    debian/changelog \
    debian/compat \
    debian/control \
    debian/copyright \
    debian/README \
    debian/rules \
    quandoparte.desktop \
    icons/quandoparte.png \
    resources/quandoparte.css \
    resources/arrivals.css \
    resources/departures.css \
    $$replace(TRANSLATIONS, .ts, .qm)

message($${OTHER_FILES})
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/bin
    } else {
        target.path = /usr/local/bin
    }
    INSTALLS += target
}

unix:!symbian {
    desktopfile.files = $${TARGET}.desktop
    maemo5 {
        desktopfile.path = /usr/share/applications/hildon
    } else {
        desktopfile.path = /usr/share/applications
    }
    INSTALLS += desktopfile
}

unix:!symbian {
    css.files = resources/$${TARGET}.css resources/arrivals.css resources/departures.css
    i18n.files = $$replace(TRANSLATIONS, .ts, .qm)
    maemo5 {
	i18n.path = /opt/usr/share/apps/$${TARGET}/i18n
	css.path = /opt/usr/share/apps/$${TARGET}/css
    } else {
	i18n.path = /usr/share/apps/$${TARGET}/i18n
	css.path = /usr/share/apps/$${TARGET}/css
    }
    icon48.files = icons/48x48/$${TARGET}.png
    icon64.files = icons/64x64/$${TARGET}.png
    icon48.path = /usr/share/icons/hicolor/48x48/apps
    icon64.path = /usr/share/icons/hicolor/64x64/apps
    INSTALLS += icon48
    INSTALLS += icon64
    INSTALLS += css
    INSTALLS += i18n
}
