#ifndef STATIONLISTPROXYMODEL_H
#define STATIONLISTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QGeoCoordinate>

QTM_USE_NAMESPACE

class StationListProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit StationListProxyModel(QObject *parent = 0);

    void setUserPosition(const QGeoCoordinate &pos);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    QGeoCoordinate m_here;
};

#endif // STATIONLISTPROXYMODEL_H
