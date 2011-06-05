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

    qDebug() << "lessThan called";

    if (role == StationListModel::PositionRole) {
        QGeoCoordinate first = left.data(role).value<QGeoCoordinate>();
        QGeoCoordinate second = right.data(role).value<QGeoCoordinate>();
        qDebug() << "PositionRole" << left.data(Qt::DisplayRole) << first << right.data(Qt::DisplayRole) << second << "Here" << m_here;
       return first.distanceTo(m_here) < second.distanceTo(m_here);
    } else {
        qDebug() << "OtherRole";
        return QString::compare(left.data(role).toString(),
                                right.data(role).toString(),
                                sortCaseSensitivity()) < 0;
    }
}

void StationListProxyModel::setUserPosition(const QtMobility::QGeoCoordinate &pos)
{
    m_here = pos;
}
