#include "stationlistproxymodel.h"
#include "stationlistmodel.h"

#include <QDebug>
#include <QGeoCoordinate>

QTM_USE_NAMESPACE

Q_DECLARE_METATYPE(QGeoCoordinate)

StationListProxyModel::StationListProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    m_here(44.5, 9.0)
{
}

bool StationListProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
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
