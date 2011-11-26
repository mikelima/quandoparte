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
#include <QWebElement>
#include <QWebFrame>
#include <QWebPage>
StationScheduleModel::StationScheduleModel(const QString &name, QObject *parent) :
    QAbstractListModel(parent),
    m_name(name)

{
    DataProvider *provider = DataProvider::instance();
    QHash<int, QByteArray> roles;
    roles[TrainRole] = "train";
    roles[DepartureStationRole] = "departureStation";
    roles[DepartureTimeRole] = "departureTime";
    roles[ArrivalStationRole] = "arrivalStation";
    roles[ArrivalTimeRole] = "ArrivalTime";
    roles[DetailsUrlRole] = "DetailsUrl";
    roles[DelayRole] = "delay";
    roles[DelayClassRole] = "delayClassRole";
    setRoleNames(roles);

    connect(provider, SIGNAL(stationScheduleReady(QByteArray,QUrl)),
            this, SLOT(parse(QByteArray,QUrl)));
}

QString & StationScheduleModel::name()
{
    return m_name;
}

void StationScheduleModel::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

StationScheduleItem parseResult(const QWebElement &result)
{
    StationScheduleItem item;
    qDebug() << "result:" << result.toPlainText();
    QWebElement current = result.findFirst("h2");
    if (!current.isNull()) {
        item.setTrain(current.toPlainText());
    }
    qDebug() << "train:" << item.train();
    return item;
}

void StationScheduleModel::parse(const QByteArray &htmlReply, const QUrl &baseUrl)
{
    Q_UNUSED(baseUrl);
    qDebug() << "--- start of query result --- cut here ------";
    qDebug() << QString::fromUtf8(htmlReply.constData());
    qDebug() << "--- end of query result ----- cut here ------";

    emit layoutAboutToBeChanged();
    beginInsertRows(QModelIndex(), 0, 0);
    QWebPage page;
    page.mainFrame()->setContent(htmlReply, "text/html", baseUrl);
    QWebElement doc = page.mainFrame()->documentElement();

    // Find the first div
    QWebElement current = doc.findFirst("div");

    QStringList departures, arrivals;
    qDebug() << "skipping to the departures";
    // Skip to the first div of class corpocentrale, which contains the first
    // departure-related contents
    while (!current.classes().contains("corpocentrale")) {
        current = current.nextSibling();
        qDebug() << "skipping to the next element";
        if (current.isNull())
            break;
    }
    // Mark every div as a departure class element; the next corpocentrale
    // marks the start of the arrivals section
    qDebug() << "marking departures";
    do {
        if (current.classes().contains("bloccorisultato")) {
            departures << current.toPlainText();
            StationScheduleItem schedule = parseResult(current);
            if (schedule.isValid()) {
                m_schedules << schedule;
            }
        }
        current = current.nextSibling();
        qDebug() << "marking as departures";
        if (current.isNull())
            break;
    } while (!current.classes().contains("corpocentrale"));

    // Mark everything as an arrival, until reaching the footer
    while (!current.classes().contains("footer")) {
        if (current.classes().contains("bloccorisultato")) {
            arrivals << current.toPlainText();
        }
        current = current.nextSibling();
        qDebug() << "marking as arrival";
        if (current.isNull())
            break;
    }

    //qDebug() << "departures list contain:";
    //qDebug() << departures;
    //qDebug() << "arrivals list contain:";
    //qDebug() << arrivals;
    emit layoutChanged();
    endInsertRows();
}

void StationScheduleModel::fetch(const QString &name)
{
    DataProvider *provider = DataProvider::instance();

    provider->fetchStationSchedule(name);
    setName(name);
}

int StationScheduleModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "there are" << m_schedules.count() << "schedules";
    return m_schedules.count();
}

QVariant StationScheduleModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "getting data for role" << role;
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() > m_schedules.count()) {
        return QVariant();
    }
    StationScheduleItem item = m_schedules[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case TrainRole:
        return QVariant::fromValue(item.train());
    case DepartureStationRole:
        return QVariant::fromValue(item.departureStation());
    case DepartureTimeRole:
        return QVariant::fromValue(item.departureTime());
    case ArrivalStationRole:
        return QVariant::fromValue(item.arrivalStation());
    case ArrivalTimeRole:
        return QVariant::fromValue(item.arrivalTime());
    case DetailsUrlRole:
        return QVariant::fromValue(item.detailsUrl());
    case DelayRole:
        return QVariant::fromValue(item.delay());
    case DelayClassRole:
        return QVariant::fromValue(item.delayClass());
    default:
        return QVariant::fromValue(QString("Unknown role requested"));
    }
}
