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

#include "stationschedulemodel.h"

#include "dataprovider.h"

#include <QDebug>

StationScheduleModel::StationScheduleModel(const QString &name, QObject *parent) :
    QStringListModel(parent),
    m_name(name)

{
}

QString & StationScheduleModel::name()
{
    return m_name;
}

void StationScheduleModel::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

void StationScheduleModel::parse(const QByteArray &htmlReply, const QUrl &baseUrl)
{
    Q_UNUSED(baseUrl);
    qDebug() << "--- start of query result --- cut here ------";
    qDebug() << htmlReply;
    qDebug() << "--- end of query result ----- cut here ------";
}

void StationScheduleModel::fetch(const QString &name)
{
    DataProvider *provider = DataProvider::instance();

    connect(provider, SIGNAL(stationScheduleReady(QByteArray,QUrl)),
            this, SLOT(parse(QByteArray,QUrl)));
    provider->fetchStationSchedule(name);
    setName(name);
}
