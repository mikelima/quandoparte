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

#include "settings.h"
#include "stationlistmodel.h"

#include <QtGlobal>
#include <QDebug>
#include <QGeoCoordinate>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
QTM_USE_NAMESPACE

Q_DECLARE_METATYPE(QGeoCoordinate)
#endif

StationListProxyModel::StationListProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    positionInfoSource(QGeoPositionInfoSource::createDefaultSource(this)),
    m_here(44.5, 9.0),
    m_filterRecentOnly(false)
{
    Settings *settings = Settings::instance();
    forceSortingMode(settings->stationListSortingMode());
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setDynamicSortFilter(true);
    if (positionInfoSource) {
        qDebug() << "position info source available";
        connect(positionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                SLOT(updatePosition(QGeoPositionInfo)));
        positionInfoSource->setUpdateInterval(5000);
    } else {
        qDebug() << "No position info source available";
    }
    connect(settings, SIGNAL(recentStationsChanged()),
            this, SLOT(updateRecentStations()));
    updateRecentStations();
}

bool StationListProxyModel::lessThan(const QModelIndex &left,
                                     const QModelIndex &right) const
{
    int role = sortRole();

    if (role == StationListModel::PositionRole) {
        QGeoCoordinate first = left.data(role).value<QGeoCoordinate>();
        QGeoCoordinate second = right.data(role).value<QGeoCoordinate>();
       return first.distanceTo(m_here) < second.distanceTo(m_here);
    } else {
        return QString::compare(left.data(role).toString(),
                                right.data(role).toString(),
                                sortCaseSensitivity()) < 0;
    }
}


void StationListProxyModel::setUserPosition(const QGeoCoordinate &pos)
{
    qDebug() << "Position is now" << pos;
    m_here = pos;
    if (sortingMode() == StationListProxyModel::DistanceSorting) {
        invalidate();
    }
}

void StationListProxyModel::setRecentStations(const QStringList &stations)
{
    qDebug() << "Recent stations are now" << stations;
    m_stations = stations;
    if (sortingMode() == StationListProxyModel::RecentUsageSorting) {
        invalidate();
    }
}

void StationListProxyModel::updateRecentStations(void)
{
    Settings *settings = Settings::instance();
    setRecentStations(settings->recentStations());
}

bool StationListProxyModel::filterAcceptsRow(int sourceRow,
                                             const QModelIndex &sourceParent) const
{
    bool acceptable;
    QModelIndex i = sourceModel()->index(sourceRow, 0, sourceParent);
    QString stationName = sourceModel()->data(i).toString();
    if (m_filterRecentOnly) {
        acceptable =  m_stations.contains(stationName);
    } else {
        acceptable = true;
    }
    return acceptable && stationName.contains(filterRegExp());
}

void StationListProxyModel::setRecentOnlyFilter(bool activation)
{
    m_filterRecentOnly = activation;
}

QString StationListProxyModel::searchPattern() const
{
    return m_searchPattern;
}

void StationListProxyModel::setSearchPattern(const QString &pattern)
{
    m_searchPattern = pattern;
    setFilterFixedString(m_searchPattern);
    qDebug() << "set Search pattern to" << pattern;
}

StationListProxyModel::SortingMode StationListProxyModel::sortingMode()
{
    return m_sortingMode;
}

void StationListProxyModel::setSortingMode(SortingMode mode)
{
    if (mode != m_sortingMode) {
        beginResetModel();
        forceSortingMode(mode);
        endResetModel();
    }
    Settings *settings = Settings::instance();
    settings->setStationListSortingMode(m_sortingMode);

    emit sortingModeChanged(mode);
}

void StationListProxyModel::forceSortingMode(SortingMode mode)
{
    m_sortingMode = mode;
    setRecentOnlyFilter(false);

    switch (mode) {
    case StationListProxyModel::AlphaSorting:
        setSortRole(Qt::DisplayRole);
        break;
    case StationListProxyModel::DistanceSorting:
        setSortRole(StationListModel::PositionRole);
        break;
    case StationListProxyModel::RecentUsageSorting:
        setRecentOnlyFilter(true);
        break;
    default:
        break;
    }
    if (mode == StationListProxyModel::DistanceSorting) {
        positionInfoSource->startUpdates();
    } else {
#if 0
        positionInfoSource->stopUpdates();
#endif
    }
    invalidate();
    sort(0);
}

void StationListProxyModel::updatePosition(const QGeoPositionInfo &update)
{
    qDebug() << "Position update received" << update;
    if (update.isValid()) {
        QGeoCoordinate newPosition = update.coordinate();
        if (newPosition.distanceTo(m_here) > 50.0) {
            setUserPosition(update.coordinate());
            invalidate();
            sort(0);
        }
    }
}
