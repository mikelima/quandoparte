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

#include "stationlistmodel.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QStandardItem>
#include <QGeoCoordinate>

QTM_USE_NAMESPACE
Q_DECLARE_METATYPE(QGeoCoordinate)

StationListModel::StationListModel(QObject *parent) :
    QStandardItemModel(parent)
{
    setRowCount(0);
}

bool StationListModel::load(const QString &filename)
{
    QFile file(filename);
    QFileInfo fi(file);

    qDebug() << "loading file:" << fi.absoluteFilePath();

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "cannot open file:" << filename;
        return false;
    }
    m_reader.setDevice(&file);
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isStartElement()) {
            if(m_reader.name() == "stations") {
                readStationsElement();
            } else {
                m_reader.raiseError(tr("Not a qpl file"));
            }
        } else {
            m_reader.readNext();
        }
    }
    file.close();
    if (m_reader.hasError()) {
        qDebug() << "parser error for:" << filename;
        return false;
    } else if (file.error() != QFile::NoError) {
        qDebug() << "file error for:" << filename;
        return false;
    }
    emit layoutChanged();
    return true;
}

void StationListModel::readStationsElement()
{
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        } else if (m_reader.isStartElement()) {
            if (m_reader.name() == "station") {
                readStationElement();
            } else {
                skipUnknownElement();
            }
        } else {
            m_reader.readNext();
        }
    }
}

void StationListModel::readStationElement()
{
    QStandardItem *item = new QStandardItem;
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            this->appendRow(item);
            m_reader.readNext();
            break;
        } else if (m_reader.isStartElement()) {
            if (m_reader.name() == "pos") {
                readPosElement(item);
            } else  if (m_reader.name() == "name") {
                readNameElement(item);
            } else {
                skipUnknownElement();
            }
        } else {
            m_reader.readNext();
        }
    }
}

void StationListModel::readPosElement(QStandardItem *item)
{
    QStringList coordinates = m_reader.readElementText().split(",");
    QGeoCoordinate pos = QGeoCoordinate(coordinates[0].toDouble(), coordinates[1].toDouble());
    item->setData(QVariant::fromValue(pos), PositionRole);
    m_reader.readElementText();
    if (m_reader.isEndElement()) {
        m_reader.readNext();
    }
}

void StationListModel::readNameElement(QStandardItem *item)
{
    item->setText(m_reader.readElementText());
    if (m_reader.isEndElement()) {
        m_reader.readNext();
    }
}

void StationListModel::skipUnknownElement()
{
    qDebug() << "skipping unknown element";

    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        } else if (!m_reader.isStartElement()) {
            skipUnknownElement();
        } else {
            m_reader.readNext();
        }
    }
}
