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

#include "settings.h"

#include <QDebug>
#include <QSettings>
#include <QStringList>

Q_DECLARE_METATYPE(StationListProxyModel::SortingMode)

Settings *Settings::instance()
{
    static Settings *settings = 0;

    if (!settings)
        settings = new Settings();
    return settings;
}

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Settings constructor called";
}

Settings::~Settings()
{
    qDebug() << "Settings destructor called";
    save();
}

void Settings::save()
{
    qDebug() << "Saving Settings to" << m_settings.fileName();

    m_settings.sync();
    dump();
}

QString Settings::queryBaseUrl()
{
    return m_settings.value("QueryURL",
                            "http://mobile.viaggiatreno.it/viaggiatreno/mobile/stazione").toString();
}

void Settings::setQueryBaseUrl(const QString &url)
{
    m_settings.setValue("QueryURL", url);
    emit queryBaseUrlChanged(m_queryBaseUrl);
}

QStringList Settings::recentStations()
{
    return m_settings.value("RecentStations").toString().split(",");
}

void Settings::setRecentStations(const QStringList &stations)
{
    m_settings.setValue("RecentStations", stations.join(","));
    emit recentStationsChanged(m_recentStations);
}

int Settings::checkingInterval()
{
    return m_settings.value("CheckInterval", 0).toInt();
}

void Settings::setCheckingInterval(int interval)
{
    m_settings.setValue("CheckInterval", interval);
    emit checkingIntervalChanged(m_checkingInterval);
}

bool Settings::stationViewPreferred()
{
    return m_stationViewPreferred;
}

void Settings::setStationViewPreferred(bool preference)
{
    m_settings.setValue("StationViewPreferred", preference);
    emit stationViewPreferredChanged(m_stationViewPreferred);
}

bool Settings::showArrivalsPreferred()
{
    return m_settings.value("StationView/ShowArrivals", false).toBool();
}

void Settings::setShowArrivalsPreferred(bool preference)
{
    m_settings.setValue("StationView/ShowArrivals", preference);
    emit showArrivalsPreferredChanged(m_showArrivalsPreferred);
}

StationListProxyModel::SortingMode Settings::stationListSortingMode()
{
    int mode = m_settings.value("StationListView/SortingMode").toInt();
    return (StationListProxyModel::SortingMode)mode;
}

void Settings::setStationListSortingMode(StationListProxyModel::SortingMode mode)
{
    m_settings.setValue("StationListView/SortingMode", mode);
    emit stationListSortingModeChanged(m_stationListSortingMode);
}
