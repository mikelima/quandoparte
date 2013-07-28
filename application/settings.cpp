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

#include <QApplication>
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
    qDebug() << "Settings constructor called";
}

Settings::~Settings()
{
    qDebug() << "Settings destructor called";
    save();
}

void Settings::save()
{
    QSettings settings;

    qDebug() << "Saving Settings to" << settings.fileName();
    settings.sync();
}

QString Settings::queryBaseUrl()
{
    QSettings settings;
    return settings.value("QueryURL",
                          "http://mobile.viaggiatreno.it/vt_pax_internet/mobile/").toString();
}

void Settings::setQueryBaseUrl(const QString &url)
{
    QSettings settings;

    settings.setValue("QueryURL", url);
    emit queryBaseUrlChanged();
}

QStringList Settings::recentStations()
{
    QSettings settings;

    return settings.value("RecentStations").toString().split(",");
}

void Settings::setRecentStations(const QStringList &stations)
{
    QSettings settings;

    settings.setValue("RecentStations", stations.join(","));
    emit recentStationsChanged();
}

int Settings::checkingInterval()
{
    QSettings settings;

    return settings.value("CheckInterval", 0).toInt();
}

void Settings::setCheckingInterval(int interval)
{
    QSettings settings;

    settings.setValue("CheckInterval", interval);
    emit checkingIntervalChanged();
}

bool Settings::autoUpdate()
{
    QSettings settings;

    bool current = settings.value("AutoUpdate", false).toBool();
    qDebug() << "AutoUpdate is" << current;
    return current;
}

void Settings::setAutoUpdate(bool preference)
{
    QSettings settings;

    settings.setValue("AutoUpdate", preference);
    qDebug() << "AutoUpdate set to" << preference;
    emit autoUpdateChanged();
}

bool Settings::stationViewPreferred()
{
    QSettings settings;

    return settings.value("StationViewPreferred", false).toBool();
}

void Settings::setStationViewPreferred(bool preference)
{
    QSettings settings;

    settings.setValue("StationViewPreferred", preference);
    emit stationViewPreferredChanged();
}

bool Settings::showArrivalsPreferred()
{
    QSettings settings;

    return settings.value("StationView/ShowArrivals", false).toBool();
}

void Settings::setShowArrivalsPreferred(bool preference)
{
    QSettings settings;

    settings.setValue("StationView/ShowArrivals", preference);
    emit showArrivalsPreferredChanged();
}

StationListProxyModel::SortingMode Settings::stationListSortingMode()
{
    QSettings settings;

    int mode = settings.value("StationListView/SortingMode").toInt();
    qDebug() << "StationListSortingMode is" << mode;
    return (StationListProxyModel::SortingMode)mode;
}

void Settings::setStationListSortingMode(StationListProxyModel::SortingMode mode)
{
    QSettings settings;

    settings.setValue("StationListView/SortingMode", mode);
    qDebug() << "StationListSortingMode set to" << mode;
    emit stationListSortingModeChanged();
}

QString Settings::versionString()
{
    return qApp->applicationVersion();
}
