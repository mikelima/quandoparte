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
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(ScheduleType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged)
    Q_ENUMS(ScheduleType)

    enum StationRoles {
        TrainRole = Qt::UserRole +1,
        DepartureStationRole,
        DepartureTimeRole,
        ArrivalStationRole,
        ArrivalTimeRole,
        DetailsUrlRole,
        DelayRole,
        DelayClassRole,
        ExpectedPlatformRole,
        ActualPlatformRole
    };

public:
    enum ScheduleType {
        DepartureSchedule,
        ArrivalSchedule
    };

    explicit StationScheduleModel(const QString &name = "", QObject *parent = 0);

    const QString &name();
    void setName(const QString &name);

    const QString &code();
    void setCode(const QString &code);

    ScheduleType type();
    void setType(ScheduleType type);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    const QString &error();
    void setError(const QString &code);

signals:
    void nameChanged();
    void codeChanged();
    void typeChanged();
    void errorChanged();

public slots:
    void fetch(const QString &name, const QString &code = QString());

private slots:
    void parse(const QByteArray &htmlReply, const QUrl &baseUrl);
    void onNetworkError(void);

private:
    QString m_name;
    QString m_code;
    QString m_error;
    QList<StationScheduleItem> m_departureSchedules;
    QList<StationScheduleItem> m_arrivalSchedules;
    ScheduleType m_scheduleType;
};

#endif // STATIONSCHEDULEMODEL_H
