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
#include "stationlistmodel.h"
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

#include <QGeoPositionInfoSource>

QTM_USE_NAMESPACE

App::App(QObject *parent) :
    QObject(parent),
    accessManager(new QNetworkAccessManager(this)),
    positionInfoSource(QGeoPositionInfoSource::createDefaultSource(this)),
    stationView(new StationView()),
    stationListModel(new StationListModel(this)),
    stationListView(new StationListView(stationListModel, stationView))
{
    stationListModel->load(dataDir() + "stations/stations.qpl");

    connect(positionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
            stationListView, SLOT(updatePosition(QGeoPositionInfo)));
    connect(stationListView, SIGNAL(stationSelected(const QString &)),
            SLOT(queryStation(const QString &)));
    connect(stationListView, SIGNAL(aboutTriggered()),
            SLOT(showAboutDialog()));
    connect(stationView, SIGNAL(aboutTriggered()),
            SLOT(showAboutDialog()));
    connect(stationView, SIGNAL(stationListSelectTriggered()),
            SLOT(showStationSelectView()));

    connect(stationView, SIGNAL(showingArrivalsChanged(bool)),
            SLOT(setShowingArrivals(bool)));
    readSettings();

    qDebug() << "found" << stationListModel->rowCount() << "stations";
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

    // Testing only: start updates rigt away.
    positionInfoSource->startUpdates();
}

App::~App()
{
    delete stationView;
    saveSettings();
}

void App::downloadFinished(void)
{
    disconnect(stationQueryReply, SIGNAL(finished()),
               this, SLOT(downloadFinished()));
    stationView->updateView(stationQueryReply->readAll());
    stationListView->hide();
    stationQueryReply->deleteLater();
    stationQueryReply = 0;
#ifdef Q_WS_MAEMO_5
    stationListView->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
#endif
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
#ifdef Q_WS_MAEMO_5
    stationListView->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
#endif
}

void App::showSettingsDialog()
{
}

void App::showAboutDialog()
{
    qDebug() << "About Dialog called";
    QString name = QApplication::instance()->applicationName();
    QString version = QApplication::instance()->applicationVersion();
    QString aboutText = QString(
                tr("<p>%1 version %2</p>"
                   "<p>Copyright (c) 2010, 2011</p>"
                   "<p>Luciano Montanaro (mikelima@cirulla.net)</p>"
                   "<p>Licensed under the GNU Public License v2 or above</p>")).arg(name).arg(version);
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

void App::setShowingArrivals(bool showArrivals)
{
    showingArrivals = showArrivals;
}

QString App::dataDir(void)
{
#ifdef Q_WS_MAEMO_5
    return QString("/opt/usr/share/apps/quandoparte/");
#else
    return QString("/usr/share/apps/quandoparte/");
#endif
}
