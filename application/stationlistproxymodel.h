#ifndef STATIONLISTPROXYMODEL_H
#define STATIONLISTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QGeoCoordinate>
#include <QStringList>

QTM_USE_NAMESPACE

class StationListProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchPattern READ searchPattern WRITE setSearchPattern)
    Q_PROPERTY(SortingMode sortingMode READ sortingMode WRITE setSortingMode)
    Q_ENUMS(SortingMode)
public:

    enum SortingMode {
        NoSorting,
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

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    virtual bool filterAcceptsRow(int sourceRow,
            const QModelIndex &sourceParent) const;

private:
    QString m_searchPattern;
    QGeoCoordinate m_here;
    QStringList m_stations;
    SortingMode m_sortingMode;
    bool m_filterRecentOnly;
};

#endif // STATIONLISTPROXYMODEL_H
