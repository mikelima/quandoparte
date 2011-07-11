/*

Copyright (C) 2011 Luciano Montanaro <mikelima@cirulla.net>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.

*/

#include "app.h"
#include "view.h"

#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QLocale>
#include <QTranslator>

#ifndef QP_VERSION
#define QP_VERSION "0.0.2"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QuandoParte");
    a.setOrganizationDomain("cirulla.net");
    a.setApplicationVersion(QP_VERSION);

    QDir::setSearchPaths("css", QStringList(DATADIR "/css"));
    QDir::setSearchPaths("stations", QStringList(DATADIR "/stations"));
    QDir::setSearchPaths("i18n", QStringList(DATADIR "/i18n"));
    QDir::setSearchPaths("qml", QStringList(DATADIR "/qml"));

#ifdef QT_KEYPAD_NAVIGATION
    QApplication::setNavigationMode(Qt::NavigationModeKeypadTabOrder);
#endif

    QString locale = QLocale::system().name();
    QTranslator translator;
    if (translator.load(QString("i18n:quandoparte_") + locale)) {
        qDebug() << "Translation for locale" << locale << "loaded";
        a.installTranslator(&translator);
    } else {
        qDebug() << "Translation for locale" << locale << "not found";
    }
#ifdef TARGET_PLATFORM_FREMANTLE
    App theApp;
#else
    View theView;
    theView.show();
#endif

    return a.exec();
}
