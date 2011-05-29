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

#include <QApplication>
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

    QString locale = QLocale::system().name();
    QTranslator translator;
    if (translator.load(QString("quandoparte_") + locale,
                        App::dataDir() + "i18n")) {
        qDebug() << "Translation for locale" << locale << "loaded";
        a.installTranslator(&translator);
    } else {
        qDebug() << "Translation for locale" << locale << "not found";
    }
    App theApp;

    return a.exec();
}
