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
    load();
}
Settings::~Settings()
{
    save();
}

void Settings::load()
{
    QSettings settings;
    m_queryBaseUrl = settings.value("QueryURL",
                                  "http://mobile.viaggiatreno.it/viaggiatreno/mobile/stazione").toString();

    m_recentStations = settings.value("RecentStations").toString().split(",");
    qDebug() << "RecentStations:" << m_recentStations;

    m_stationViewPreferred = settings.value("StationViewPreferred", false).toBool();
    qDebug() << "StationsViewPreferred:" << m_stationViewPreferred;

    m_checkingInterval = settings.value("CheckInterval", 0).toInt();
    qDebug() << "CheckInterval:" << m_checkingInterval;

    m_showArrivalsPreferred = settings.value("StationView/ShowArrivals", false).toBool();
    qDebug() << "ShowArrivalsPreferred:" << m_showArrivalsPreferred;
}

void Settings::save()
{
    QSettings settings;

    qDebug() << "Saving Settings to" << settings.fileName();

    settings.setValue("QueryURL", m_queryBaseUrl);
    settings.setValue("RecentStations", m_recentStations.join(","));
    settings.setValue("CheckInterval", m_checkingInterval);
    settings.setValue("StationViewPreferred", m_stationViewPreferred);
    settings.setValue("StationView/ShowArrivals", m_stationViewPreferred);
}

QString Settings::queryBaseUrl()
{
    return m_queryBaseUrl;
}

void Settings::setQueryBaseUrl(const QString &url)
{
    m_queryBaseUrl = url;
    emit queryBaseUrlChanged(m_queryBaseUrl);
}

QStringList Settings::recentStations()
{
    return m_recentStations;
}

void Settings::setRecentStations(const QStringList &stations)
{
    m_recentStations = stations;
    emit recentStationsChanged(m_recentStations);
}

int Settings::checkingInterval()
{
    return m_checkingInterval;
}

void Settings::setCheckingInterval(int interval)
{
    m_checkingInterval = interval;

    emit checkingIntervalChanged(m_checkingInterval);
}

bool Settings::stationViewPreferred()
{
    return m_stationViewPreferred;
}

void Settings::setStationViewPreferred(bool preference)
{
    m_stationViewPreferred = preference;
    emit stationViewPreferredChanged(m_stationViewPreferred);
}

bool Settings::showArrivalsPreferred()
{
    return m_showArrivalsPreferred;
}

void Settings::setShowArrivalsPreferred(bool preference)
{
    m_showArrivalsPreferred = preference;
    emit showArrivalsPreferredChanged(m_showArrivalsPreferred);
}