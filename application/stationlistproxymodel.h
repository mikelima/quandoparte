#ifndef STATIONLISTPROXYMODEL_H
#define STATIONLISTPROXYMODEL_H

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

#include <QSortFilterProxyModel>
#include <QGeoCoordinate>
#include <QGeoPositionInfoSource>
#include <QMetaType>
#include <QStringList>

QTM_USE_NAMESPACE

class StationListProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchPattern READ searchPattern WRITE setSearchPattern)
    Q_PROPERTY(SortingMode sortingMode READ sortingMode WRITE setSortingMode NOTIFY sortingModeChanged)
    Q_ENUMS(SortingMode)
public:

    enum SortingMode {
        AlphaSorting,
        DistanceSorting,
        RecentUsageSorting
    };

    explicit StationListProxyModel(QObject *parent = 0);

    QString searchPattern() const;
    void setSearchPattern(const QString &pattern);

    SortingMode sortingMode();
    void setSortingMode(SortingMode mode);

    Q_INVOKABLE void setUserPosition(const QGeoCoordinate &pos);
    Q_INVOKABLE void setRecentStations(const QStringList &stations);
    Q_INVOKABLE void setRecentOnlyFilter(bool);

signals:
    void sortingModeChanged(SortingMode mode);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    virtual bool filterAcceptsRow(int sourceRow,
            const QModelIndex &sourceParent) const;

private slots:
    void updatePosition(const QGeoPositionInfo &update);

private:
    QString m_searchPattern;
    QGeoPositionInfoSource *positionInfoSource;
    QGeoCoordinate m_here;
    QStringList m_stations;
    SortingMode m_sortingMode;
    bool m_filterRecentOnly;
};

Q_DECLARE_METATYPE(StationListProxyModel::SortingMode)

#endif // STATIONLISTPROXYMODEL_H
