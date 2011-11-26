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

#ifndef STATIONSCHEDULEITEM_H
#define STATIONSCHEDULEITEM_H

#include <QSharedDataPointer>

class StationScheduleItemData;

class StationScheduleItem
{
public:
    StationScheduleItem();
    StationScheduleItem(const StationScheduleItem &);
    StationScheduleItem &operator=(const StationScheduleItem &);
    ~StationScheduleItem();

    QString &train();
    void setTrain(const QString &value);

    QString &departureStation();
    void setDepartureStation(const QString &value);

    QString &departureTime();
    void setDepartureTime(const QString &value);

    QString &arrivalStation();
    void setArrivalStation(const QString &value);

    QString &arrivalTime();
    void setArrivalTime(const QString &value);

    QString &detailsUrl();
    void setDetailsUrl(const QString &value);

    QString &delay();
    void setDelay(const QString &value);

    int delayClass();
    void setDelayClass(const int value);

    bool isValid();
private:
    QSharedDataPointer<StationScheduleItemData> d;
};

#endif // STATIONSCHEDULEITEM_H
