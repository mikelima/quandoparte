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

#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QUrl;

class DataProvider : public QObject
{
    Q_OBJECT
public:
    explicit DataProvider(QObject *parent = 0);

signals:
    void stationScheduleReady(const QString &result, const QUrl &url);

public slots:
    void stationSchedule(const QString &station);
    void updateStation();

private slots:
    void onStationScheduleReady(void);

private:
    QNetworkAccessManager *accessManager;
    QNetworkReply *stationQueryReply;
};

#endif // DATAPROVIDER_H
