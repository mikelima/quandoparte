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
#ifndef TARGET_PLATFORM_SAILFISH
#include <QGeoCoordinate>
#include <QGeoPositionInfoSource>
#endif
#include <QMetaType>
#include <QStringList>

#ifndef TARGET_PLATFORM_SAILFISH
QTM_USE_NAMESPACE
#endif

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

#ifndef TARGET_PLATFORM_SAILFISH
    Q_INVOKABLE void setUserPosition(const QGeoCoordinate &pos);
#endif
    Q_INVOKABLE void setRecentStations(const QStringList &stations);
    Q_INVOKABLE void setRecentOnlyFilter(bool);

signals:
    void sortingModeChanged(SortingMode mode);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    virtual bool filterAcceptsRow(int sourceRow,
            const QModelIndex &sourceParent) const;

private:
    void forceSortingMode(SortingMode mode);

private slots:
#ifndef TARGET_PLATFORM_SAILFISH
    void updatePosition(const QGeoPositionInfo &update);
#endif
    void updateRecentStations(void);
private:
    QString m_searchPattern;
#ifndef TARGET_PLATFORM_SAILFISH
    QGeoPositionInfoSource *positionInfoSource;
    QGeoCoordinate m_here;
#endif
    QStringList m_stations;
    SortingMode m_sortingMode;
    bool m_filterRecentOnly;
};

Q_DECLARE_METATYPE(StationListProxyModel::SortingMode)

#endif // STATIONLISTPROXYMODEL_H
