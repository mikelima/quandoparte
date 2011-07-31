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
#include "dataprovider.h"
#include "stationview.h"
#include "stationlistmodel.h"
#include "stationlistview.h"
#include "settingsdialog.h"
#include "settings.h"

#include <QDebug>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QUrl>

#include <QGeoPositionInfoSource>

// Constants
static const int RECENT_STATIONS_MAX_COUNT = 10;

QTM_USE_NAMESPACE

App::App(QObject *parent) :
    QObject(parent),
    dataProvider(new DataProvider(this)),
    checkingTimer(new QTimer(this)),
    stationView(new StationView()),
    stationListModel(new StationListModel(this)),
    stationListView(new StationListView(stationListModel, stationView))
{
    stationListModel->load("stations:stations.qpl");

    connect(dataProvider, SIGNAL(stationScheduleReady(QByteArray)),
            SLOT(downloadFinished(QByteArray)));

    connect(stationListView, SIGNAL(stationSelected(QString)),
            SLOT(queryStation(QString)));

    connect(stationListView, SIGNAL(aboutTriggered()),
            SLOT(showAboutDialog()));
    connect(stationView, SIGNAL(aboutTriggered()),
            SLOT(showAboutDialog()));

    connect(stationListView, SIGNAL(settingsChangeRequested()),
            SLOT(showSettingsDialog()));
    connect(stationView, SIGNAL(settingsChangeRequested()),
            SLOT(showSettingsDialog()));

    connect(stationView, SIGNAL(stationListSelectTriggered()),
            SLOT(showStationSelectView()));

    readSettings();

    qDebug() << "found" << stationListModel->rowCount() << "stations";

    connect(checkingTimer, SIGNAL(timeout()), SLOT(updateStation()));
    stationView->show();
    Settings *settings = Settings::instance();
    if (settings->recentStations().isEmpty() || !settings->stationViewPreferred()) {
        stationListView->show();
    } else {
        updateStation();
    }
}

App::~App()
{
    saveSettings();
    disconnect();
    delete stationView;
}

void App::downloadFinished(const QByteArray &data)
{
    stationView->updateView(data);
    stationListView->hide();
#ifdef Q_WS_MAEMO_5
    stationListView->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
#endif
}

void App::queryStation(const QString &station)
{
    dataProvider->stationSchedule(station);
#ifdef Q_WS_MAEMO_5
    stationListView->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
#endif
}

void App::updateStation()
{
    if (!stationListView->isVisible()) {
        dataProvider->updateStation();
    }
}

void App::showSettingsDialog()
{
    qDebug() << "Settings Dialog called";

    SettingsDialog *dialog = new SettingsDialog(stationView);
    if (dialog->exec() == QDialog::Accepted) {
        readSettings();
    }
    delete dialog;
}

void App::showAboutDialog()
{
    qDebug() << "About Dialog called";
    QString name = QApplication::instance()->applicationName();
    QString version = QApplication::instance()->applicationVersion();
    QString aboutText = QString(
                tr("<h2>"
                   "<a href='http://quandoparte.garage.maemo.org'>%1</a> version %2"
                   "</h2>"
                   "<p>Copyright (c) 2010, 2011</p>"
                   "<p>Luciano Montanaro (mikelima@cirulla.net)</p>"
                   "<p>Licensed under the GNU Public License v2 or above</p>"
                   "<p>Station geolocation data from "
                   "<a href='http://www.openstreetmap.org'>OpenStreetMap</a>"
                   "</p>"
                   "<p>Realtime train data from "
                   "<a href='http://mobile.viaggiatreno.it'>Viaggiatreno</a>"
                   "</p>")).arg(name).arg(version);
    QMessageBox::about(stationView, name, aboutText);
}

void App::showStationSelectView(void)
{
    stationListView->show();
}

void App::readSettings(void)
{
    Settings *settings = Settings::instance();
    stationView->setBaseUrl(settings->queryBaseUrl());

    /*
       I would use > 0 here, but people may have an old settings file with a 2
       seconds timeout which is way too short.
       As a workaround I consider anything less than 30 seconds as too short
       and disable the timer.
    */
    if (settings->checkingInterval() > 30000) {
        checkingTimer->setInterval(settings->checkingInterval());
        checkingTimer->start();
    } else {
        checkingTimer->setInterval(-1);
        checkingTimer->stop();
    }
}

void App::saveSettings(void)
{
    Settings::instance()->save();
}

QString App::dataDir(void)
{
    return QString(DATADIR);
}
