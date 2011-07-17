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
    /*
    QModelIndex first = index(0, 0);
    QModelIndex last = index(rowCount(), columnCount());
    emit dataChanged(first, last);
    */
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
    qDebug() << "pos:" << pos;
    m_reader.readElementText();
    if (m_reader.isEndElement()) {
        m_reader.readNext();
    }
}

void StationListModel::readNameElement(QStandardItem *item)
{
    item->setText(m_reader.readElementText());
    qDebug() << "name:" << item->text();
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
