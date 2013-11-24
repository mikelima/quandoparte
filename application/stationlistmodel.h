#ifndef STATIONLISTMODEL_H
#define STATIONLISTMODEL_H

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

#include <QAbstractItemModel>
#include <QSet>
#include <QXmlStreamReader>

#include "stationitem.h"

class StationItem;
class StationListModel;

class StationListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(StationListRole)
    Q_PROPERTY(int count READ rowCount)

public:
    enum StationListRole {
        PositionRole = Qt::UserRole + 1, //< QGeoCoordinate - Station coordinate
        StationCodeRole, //< QString - Station Code (Precise name if the Display name is known to fail)
        RecentIndicatorRole, //<bool - If the station has been recently looked up
        FavoriteIndicatorRole, //<bool - If the station has been marked as favorite
        LongitudeRole, //< double - Longitude of the station
        LatitudeRole, //< double - Latitude of the station
        SectionRole //< Qstring - The section the station belongs to (depends on the sorting mode)
    };

    explicit StationListModel(QObject *parent = 0);

    bool load(const QString &filename);

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE Qt::ItemFlags flags(const QModelIndex &index) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE bool setData(const QModelIndex &index, QVariant &value, int role = Qt::EditRole);

signals:

public slots:

private:
    void readStationsElement();
    void readStationElement();
    void readPosElement(StationItem &item);
    void readNameElement(StationItem &item);
    void readCodeElement(StationItem &item);
    void skipUnknownElement(const QString &name = QString());

    QXmlStreamReader m_reader;
    QList<StationItem> m_stations;
    QSet<QString> m_favorites;
};

#endif // STATIONLISTMODEL_H
