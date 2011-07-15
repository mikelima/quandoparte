#ifndef STATIONLISTPROXYMODEL_H
#define STATIONLISTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QGeoCoordinate>
#include <QStringList>

QTM_USE_NAMESPACE

class StationListProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit StationListProxyModel(QObject *parent = 0);
    Q_INVOKABLE void setUserPosition(const QGeoCoordinate &pos);
    Q_INVOKABLE void setRecentStations(const QStringList &stations);
    Q_INVOKABLE void setRecentOnlyFilter(bool);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    virtual bool filterAcceptsRow(int sourceRow,
            const QModelIndex &sourceParent) const;

private:
    QGeoCoordinate m_here;
    QStringList m_stations;
    bool m_filterRecentOnly;
};

#endif // STATIONLISTPROXYMODEL_H
