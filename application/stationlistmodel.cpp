#include "stationlistmodel.h"

#include <QFile>
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

    qDebug() << "loading filename:" << filename;

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "cannot open file:" << filename;
        return false;
    }
    reader.setDevice(&file);
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if(reader.name() == "stations") {
                readStationsElement();
            } else {
                reader.raiseError(tr("Not a qpl file"));
            }
        } else {
            reader.readNext();
        }
    }
    file.close();
    if (reader.hasError()) {
        qDebug() << "parser error for:" << filename;
        return false;
    } else if (file.error() != QFile::NoError) {
        qDebug() << "file error for:" << filename;
        return false;
    }
    return true;
}

void StationListModel::readStationsElement()
{
    qDebug() << "reading stations element";

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        } else if (reader.isStartElement()) {
            if (reader.name() == "station") {
                readStationElement();
            } else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void StationListModel::readStationElement()
{
    qDebug() << "reading station element";

    QStandardItem *item = new QStandardItem;
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            this->appendRow(item);
            reader.readNext();
            break;
        } else if (reader.isStartElement()) {
            if (reader.name() == "pos") {
                readPosElement(item);
            } else  if (reader.name() == "name") {
                readNameElement(item);
            } else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void StationListModel::readPosElement(QStandardItem *item)
{
    qDebug() << "reading pos element";

    QStringList coordinates = reader.readElementText().split(",");
    QGeoCoordinate pos = QGeoCoordinate(coordinates[0].toDouble(), coordinates[1].toDouble());
    item->setData(QVariant::fromValue(pos));
    qDebug() << "pos:" << pos;
    reader.readElementText();
    if (reader.isEndElement()) {
        reader.readNext();
    }
}

void StationListModel::readNameElement(QStandardItem *item)
{
    qDebug() << "reading name element";

    item->setText(reader.readElementText());
    qDebug() << "name:" << item->text();
    if (reader.isEndElement()) {
        reader.readNext();
    }
}

void StationListModel::skipUnknownElement()
{
    qDebug() << "skipping unknown element";

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        } else if (!reader.isStartElement()) {
            skipUnknownElement();
        } else {
            reader.readNext();
        }
    }
}
