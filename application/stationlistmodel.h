#ifndef STATIONLISTMODEL_H
#define STATIONLISTMODEL_H

#include <QStandardItemModel>
#include <QXmlStreamReader>

class QStandardItem;

class StationListModel : public QStandardItemModel
{
    Q_OBJECT

    enum StationListRoles {
        PositionRole = Qt::UserRole
    };
public:
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

    QXmlStreamReader reader;
};

#endif // STATIONLISTMODEL_H
