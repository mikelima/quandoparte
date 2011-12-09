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

static void parseDelayClass(const QWebElement &element, StationScheduleItem &item)
{
    if (!element.isNull()) {
        QWebElement image = element.findFirst("img");
        if (!image.isNull()) {
            int delayClass = 42;
            QString imageName = image.attribute("src");
            if (!imageName.isEmpty()) {
                QRegExp delayClassRegexp("pallinoRit([0-9])\\.png");
                int pos = delayClassRegexp.indexIn(imageName);
                qDebug() << "regexp matched at pos:" << pos << "match:" << delayClassRegexp.cap(0);
                delayClass =  (pos >= 0) ? delayClassRegexp.cap(1).toInt() : 0;
            }
            item.setDelayClass(delayClass);
        } else {
            qDebug() << "img not found";
        }
    } else {
        qDebug() << "div.bloccotreno not found";
    }
}

static void parseDetailsUrl(const QWebElement &element, StationScheduleItem &item)
{
    if (!element.isNull()) {
        QWebElement link = element.findFirst("a");
        QString url = link.attribute("href");
        item.setDetailsUrl(url);
    } else {
        qDebug() << "link not found";
    }
}

static void parseTrain(const QString &text, StationScheduleItem &item)
{
    QRegExp filter("^(Per|Da) (.*)\\n"
                   "Delle ore (.*)\n"
                   "Binario Previsto: (.*)\n"
                   "Binario Reale: (.*)\n"
                   "(.*)$");
    int pos = filter.indexIn(text);
    if (pos >= 0) {
        if (filter.cap(1) == "Per") {
            item.setDepartureStation(filter.cap(2));
            item.setDepartureTime(filter.cap(3));
        } else {
            item.setArrivalStation(filter.cap(2));
            item.setArrivalTime(filter.cap(3));
        }
        item.setDelay(filter.cap(6));
    } else {
        qDebug() << "could not parse" << text;
    }
}

StationScheduleItem parseResult(const QWebElement &result)
{
    StationScheduleItem item;

    QWebElement current = result.findFirst("h2");
    if (!current.isNull()) {
        item.setTrain(current.toPlainText());
    }
    parseDetailsUrl(result, item);
    current = result.findFirst("div.bloccotreno");
    parseDelayClass(current, item);
    QString rawText = current.toPlainText();
    parseTrain(rawText, item);

    qDebug() << "train:" << item.train();
    qDebug() << "delayClass:" << item.delayClass();
    qDebug() << "detailsUrl:" << item.detailsUrl();
    qDebug() << "departureStation:" << item.departureStation();
    qDebug() << "departureTime:" << item.departureTime();
    qDebug() << "arrivalStation:" << item.arrivalStation();
    qDebug() << "arrivalTime:" << item.arrivalTime();
    qDebug() << "delay:" << item.delay();
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
                m_departureSchedules << schedule;
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
            StationScheduleItem schedule = parseResult(current);
            if (schedule.isValid()) {
                m_arrivalSchedules << schedule;
            }
        }
        current = current.nextSibling();
        qDebug() << "marking as arrival";
        if (current.isNull())
            break;
    }
    endInsertRows();
    emit layoutChanged();
}

void StationScheduleModel::fetch(const QString &name)
{
    DataProvider *provider = DataProvider::instance();

    provider->fetchStationSchedule(name);
    setName(name);
}

int StationScheduleModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "schedule.count" << m_departureSchedules.count();
    return m_departureSchedules.count();
}

QVariant StationScheduleModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "getting data for role" << role;
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= m_departureSchedules.count()) {
        return QVariant();
    }
    StationScheduleItem item = m_departureSchedules[index.row()];
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
