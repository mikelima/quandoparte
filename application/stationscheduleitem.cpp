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

#include "stationscheduleitem.h"
#include <QSharedData>
#include <QString>

class StationScheduleItemData : public QSharedData {
public:
    QString train;
    QString departureStation;
    QString departureTime;
    QString arrivalStation;
    QString arrivalTime;
    QString detailsUrl;
    QString delay;
    QString expectedPlatform;
    QString actualPlatform;
    int delayClass;
};

StationScheduleItem::StationScheduleItem() : d(new StationScheduleItemData)
{
}

StationScheduleItem::StationScheduleItem(const StationScheduleItem &rhs) : d(rhs.d)
{
}

StationScheduleItem &StationScheduleItem::operator=(const StationScheduleItem &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

StationScheduleItem::~StationScheduleItem()
{
}

QString &StationScheduleItem::train()
{
    return d->train;
}

void StationScheduleItem::setTrain(const QString &value)
{
    d->train = value;
}

QString &StationScheduleItem::departureStation()
{
    return d->departureStation;
}

void StationScheduleItem::setDepartureStation(const QString &value)
{
    d->departureStation = value;
}

QString &StationScheduleItem::departureTime()
{
    return d->departureTime;
}

void StationScheduleItem::setDepartureTime(const QString &value)
{
    d->departureTime = value;
}

QString &StationScheduleItem::arrivalStation()
{
    return d->arrivalStation;
}

void StationScheduleItem::setArrivalStation(const QString &value)
{
    d->arrivalStation = value;
}

QString &StationScheduleItem::arrivalTime()
{
    return d->arrivalTime;
}

void StationScheduleItem::setArrivalTime(const QString &value)
{
    d->arrivalTime = value;
}

QString &StationScheduleItem::detailsUrl()
{
    return d->detailsUrl;
}

void StationScheduleItem::setDetailsUrl(const QString &value)
{
    d->detailsUrl = value;
}

QString &StationScheduleItem::delay()
{
    return d->delay;
}

void StationScheduleItem::setDelay(const QString &value)
{
    d->delay = value;
}

int StationScheduleItem::delayClass()
{
    return d->delayClass;
}

void StationScheduleItem::setDelayClass(int value)
{
    d->delayClass = value;
}

QString &StationScheduleItem::expectedPlatform()
{
    return d->expectedPlatform;
}

void StationScheduleItem::setExpectedPlatform(const QString &value)
{
    d->expectedPlatform = value;
}

QString &StationScheduleItem::actualPlatform()
{
    return d->actualPlatform;
}

void StationScheduleItem::setActualPlatform(const QString &value)
{
    d->actualPlatform = value;
}

bool StationScheduleItem::isValid()
{
    return !d->train.isEmpty();
}
