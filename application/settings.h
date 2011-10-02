#ifndef SETTINGS_H
#define SETTINGS_H

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

#include "stationlistproxymodel.h"
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString queryBaseUrl
               READ queryBaseUrl WRITE setQueryBaseUrl
               NOTIFY queryBaseUrlChanged)
    Q_PROPERTY(QStringList recentStations
               READ recentStations WRITE setRecentStations
               NOTIFY recentStationsChanged)
    Q_PROPERTY(int checkingInterval
               READ checkingInterval WRITE setCheckingInterval
               NOTIFY checkingIntervalChanged)
    Q_PROPERTY(bool stationViewPreferred
               READ stationViewPreferred WRITE setStationViewPreferred
               NOTIFY stationViewPreferredChanged)
    Q_PROPERTY(bool showArrivalsPreferred
               READ showArrivalsPreferred WRITE setShowArrivalsPreferred
               NOTIFY showArrivalsPreferredChanged)

    Q_PROPERTY(StationListProxyModel::SortingMode stationListSortingMode
               READ stationListSortingMode WRITE setStationListSortingMode
               NOTIFY stationListSortingModeChanged)
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    Q_INVOKABLE static Settings *instance();

    Q_INVOKABLE void save(void);

    QString queryBaseUrl();
    void setQueryBaseUrl(const QString &url);

    QStringList recentStations();
    void setRecentStations(const QStringList &stations);

    int checkingInterval();
    void setCheckingInterval(int);

    bool stationViewPreferred();
    void setStationViewPreferred(bool);

    bool showArrivalsPreferred();
    void setShowArrivalsPreferred(bool);

    StationListProxyModel::SortingMode stationListSortingMode();
    void setStationListSortingMode(StationListProxyModel::SortingMode mode);

signals:
    void queryBaseUrlChanged(const QString &);
    void recentStationsChanged(const QStringList &);
    void checkingIntervalChanged(int);
    void stationViewPreferredChanged(bool);
    void showArrivalsPreferredChanged(bool);
    void stationListSortingModeChanged(StationListProxyModel::SortingMode mode);

public slots:

private:
    QSettings m_settings;
};

#endif // SETTINGS_H
