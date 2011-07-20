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
#include "stationlistmodel.h"

#include <QDebug>
#include <QGeoCoordinate>

QTM_USE_NAMESPACE

Q_DECLARE_METATYPE(QGeoCoordinate)

StationListProxyModel::StationListProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    m_here(44.5, 9.0),
    m_sortingMode(NoSorting),
    m_filterRecentOnly(false)
{
    QHash<int, QByteArray> roles;
    roles[StationListModel::PositionRole] = "position";
    setRoleNames(roles);

    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
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

void StationListProxyModel::setUserPosition(const QtMobility::QGeoCoordinate &pos)
{
    m_here = pos;
}

void StationListProxyModel::setRecentStations(const QStringList &stations)
{
    m_stations = stations;
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
        qDebug() << "setSorting Mode" << mode << m_sortingMode << "called";
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
        case StationListProxyModel::NoSorting:
        default:
            break;
        }
        invalidate();
        sort(0);
        emit sortingModeChanged(mode);
    }
}
