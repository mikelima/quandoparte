/*

Copyright (C) 2013 Luciano Montanaro <mikelima@cirulla.net>

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

#include "stationitem.h"
#include <QGeoCoordinate>
#include <QSharedData>
#include <QString>

class StationItemData : public QSharedData {
public:
    QGeoCoordinate position;
    QString name;
    QString code;
};

StationItem::StationItem() : d(new StationItemData)
{
}

StationItem::StationItem(const StationItem &rhs) : d(rhs.d)
{
}

StationItem &StationItem::operator=(const StationItem &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

StationItem::~StationItem()
{
}

QString &StationItem::name()
{
    return d->name;
}

void StationItem::setName(const QString &value)
{
    d->name = value;
}

QString &StationItem::code()
{
    return d->code;
}

void StationItem::setCode(const QString &value)
{
    d->code = value;
}

QGeoCoordinate &StationItem::position()
{
    return d->position;
}

void StationItem::setPosition(const QGeoCoordinate &value)
{
    d->position = value;
}

bool StationItem::isValid()
{
    return !d->name.isEmpty();
}
