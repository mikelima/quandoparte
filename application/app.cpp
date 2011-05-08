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
#include "stationview.h"
#include "stationlistview.h"
#include "settingsdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSettings>
#include <QUrl>

App::App(QObject *parent) :
    QObject(parent),
    accessManager(new QNetworkAccessManager(this)),
    stationView(new StationView(NULL)),
    stationListView(new StationListView(stationView))
{
    connect(stationListView, SIGNAL(stationSelected(const QString &)),
            SLOT(queryStation(const QString &)));
    connect(stationView, SIGNAL(aboutTriggered()),
            SLOT(showAboutDialog()));
    connect(stationView, SIGNAL(stationListSelectTriggered()),
            SLOT(showStationSelectView()));

    readSettings();

#if defined(Q_WS_S60)
    stationView->showMaximized();
#else
    stationView->show();
#endif

    if (stationName.isEmpty()) {
#if defined(Q_WS_S60)
        stationListView->showMaximized();
#else
        stationListView->show();
#endif
    }
}

void App::downloadFinished(void)
{
    disconnect(stationQueryReply, SIGNAL(finished()),
               this, SLOT(downloadFinished()));
    stationView->updateView(stationQueryReply->readAll());
    stationListView->hide();
    stationQueryReply->deleteLater();
    stationQueryReply = 0;
}

void App::queryStation(const QString &station)
{
    QNetworkRequest request;
    request.setUrl(queryBaseUrl);
    const QString queryString = "stazione=" + station;
    const QByteArray query(queryString.toLocal8Bit());
    stationQueryReply = accessManager->post(request, query);
    connect(stationQueryReply, SIGNAL(finished()),
            this, SLOT(downloadFinished()));
}

void App::showSettingsDialog()
{
}

void App::showAboutDialog()
{
    qDebug() << "About Dialog called";
    QString name = QApplication::instance()->applicationName();
    QString aboutText = QString(
                tr("<p>%1</p>"
                   "<p>Copyright (c) 2010</p>"
                   "<p>Luciano Montanaro (mikelima@cirulla.net)</p>"
                   "<p>Licensed under the GNU Public License v2 or above</p>")).arg(name);
    QMessageBox::about(stationView, name, aboutText);
}

void App::showStationSelectView(void)
{
    stationListView->show();
}

void App::readSettings(void)
{
    QSettings settings;
    queryBaseUrl = settings.value("QueryURL",
                                  "http://mobile.viaggiatreno.it/viaggiatreno/mobile/stazione").toString();
    stationView->setBaseUrl(queryBaseUrl);

    stationName = settings.value("CurrentStation").toString();
    showingArrivals = settings.value("ShowingArrivals", false).toBool();
    checkingInterval = settings.value("CheckInterval", 2000).toInt();
}

void App::saveSettings(void)
{
    QSettings settings;
    settings.setValue("QueryURL", queryBaseUrl);
    settings.value("CurrentStation", stationName);
    settings.value("ShowingArrivals", showingArrivals);
    settings.value("CheckInterval", checkingInterval);
}
