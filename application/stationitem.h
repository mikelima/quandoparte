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

#ifndef STATIONITEM_H
#define STATIONITEM_H

#include <QSharedDataPointer>
#include <QGeoCoordinate>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
QTM_USE_NAMESPACE
#endif

class StationItemData;

class StationItem
{
public:
    StationItem();
    StationItem(const StationItem &);
    StationItem &operator=(const StationItem &);
    ~StationItem();

    QString &name();
    void setName(const QString &value);

    QString &code();
    void setCode(const QString &value);

    QGeoCoordinate &position();
    void setPosition(const QGeoCoordinate &value);

    bool isValid();
private:
    QSharedDataPointer<StationItemData> d;
};

#endif // STATIONITEM_H
