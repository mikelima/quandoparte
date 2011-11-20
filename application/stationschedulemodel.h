/*

Copyright (C) 2011 mikelima

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

#ifndef STATIONSCHEDULEMODEL_H
#define STATIONSCHEDULEMODEL_H

#include "stationscheduleitem.h"

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>

class StationScheduleModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    enum StationRoles {
        RefRole = Qt::UserRole +1,
        DepartureStationRole,
        DepartureTimeRole,
        ArrivalStationRole,
        ArrivalTimeRole,
        DetailsUrlRole,
        DelayRole,
        DelayClassRole
    };

public:
    explicit StationScheduleModel(const QString &name = "", QObject *parent = 0);

    QString &name();
    void setName(const QString &name);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:
    void nameChanged();

public slots:
    void fetch(const QString &name);

private slots:
    void parse(const QByteArray &htmlReply, const QUrl &baseUrl);

private:
    QString m_name;
    QList<StationScheduleItem> m_schedules;
};

#endif // STATIONSCHEDULEMODEL_H
