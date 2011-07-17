#include "stationlistproxymodel.h"
#include "stationlistmodel.h"

#include <QDebug>
#include <QGeoCoordinate>

QTM_USE_NAMESPACE

Q_DECLARE_METATYPE(QGeoCoordinate)

StationListProxyModel::StationListProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    m_here(44.5, 9.0),
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
}
