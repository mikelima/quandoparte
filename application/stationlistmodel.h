#ifndef STATIONLISTMODEL_H
#define STATIONLISTMODEL_H

#include <QStandardItemModel>
#include <QXmlStreamReader>

class QStandardItem;
class StationListModel;

class StationListModel : public QStandardItemModel
{
    Q_OBJECT
    Q_ENUMS(StationListRole)
public:
    enum StationListRole {
        PositionRole = Qt::UserRole + 1, //< QGeoCoordinate - Station coordinate
        StationIdRole, //< QString - Station Id (Precise name if the Display name is known to fail)
        RecentIndicatorRole //<bool - If the station has been recently looked up
    };

    explicit StationListModel(QObject *parent = 0);

    bool load(const QString &filename);

signals:

public slots:

private:
    void readStationsElement();
    void readStationElement();
    void readPosElement(QStandardItem *item);
    void readNameElement(QStandardItem *item);
    void skipUnknownElement();

    QXmlStreamReader m_reader;
};

#endif // STATIONLISTMODEL_H
