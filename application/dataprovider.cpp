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

#include "dataprovider.h"
#include "settings.h"
#include "stationschedulemodel.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSharedPointer>
#if 0
#include <QWebElement>
#include <QWebFrame>
#include <QWebPage>
#endif

// Constants
static const int RECENT_STATIONS_MAX_COUNT = 10;

// Class methods

DataProvider *DataProvider::instance()
{
    static DataProvider *dataProvider = 0;

    if (!dataProvider)
        dataProvider = new DataProvider(0);
    return dataProvider;
}

DataProvider::DataProvider(QObject *parent) :
    QObject(parent),
    accessManager(new QNetworkAccessManager(this)),
    stationQueryReply(0)
{
}

void DataProvider::fetchStationSchedule(const QString &station,
                                        const QString &stationCode)
{
    QNetworkRequest request;
    Settings *settings = Settings::instance();
    request.setUrl(settings->queryBaseUrl() + "stazione");
    qDebug() << "fetching schedule for station:" << station << "code:" << stationCode;
    const QString queryString =
            stationCode.isEmpty() ? "stazione=" + station :
                                    "codiceStazione=" + stationCode;
    const QByteArray query(queryString.toLocal8Bit());
    stationQueryReply = accessManager->post(request, query);
    connect(stationQueryReply, SIGNAL(metaDataChanged()),
            SLOT(onStationQueryMetadataChanged()));
    connect(stationQueryReply, SIGNAL(finished()),
            SLOT(onStationScheduleFetched()));
    connect(stationQueryReply, SIGNAL(error(QNetworkReply::NetworkError)),
            SLOT(onNetworkError(QNetworkReply::NetworkError)));
    QStringList recentStations = settings->recentStations();
    recentStations.push_front(station);
    recentStations.removeDuplicates();
    if (recentStations.count() > RECENT_STATIONS_MAX_COUNT) {
        recentStations.pop_back();
    }
    settings->setRecentStations(recentStations);
}

void DataProvider::updateStation()
{
    Settings *settings = Settings::instance();

    qDebug() << "updating station data";
    if (!settings->recentStations().isEmpty()) {
        fetchStationSchedule(settings->recentStations().front());
    }
}

void DataProvider::onStationScheduleFetched()
{
    disconnect(stationQueryReply);

    QVariant httpStatus = stationQueryReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (httpStatus.isValid()) {
        qDebug() << "Metadata changed, Http status is:" << httpStatus.toInt();
    }
    emit stationScheduleReady(stationQueryReply->readAll(), stationQueryReply->url());
    stationQueryReply->deleteLater();
    stationQueryReply = 0;
}

void DataProvider::onStationQueryMetadataChanged(void)
{
}

void DataProvider::onNetworkError(QNetworkReply::NetworkError errorCode)
{
    switch (errorCode) {
    case QNetworkReply::NoError:
        qDebug() << "No Network error" << errorCode;
        break;
    default:
        qDebug() << "Network error" << errorCode;
        emit error();
        break;
    }
}
