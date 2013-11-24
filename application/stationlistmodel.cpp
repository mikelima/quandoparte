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
#include "settings.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QStandardItem>
#include <QGeoCoordinate>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
QTM_USE_NAMESPACE
Q_DECLARE_METATYPE(QGeoCoordinate)
#endif

StationListModel::StationListModel(QObject *parent) :
    QAbstractListModel(parent)
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    setRoleNames(roleNames());
#endif
    Settings *settings = Settings::instance();
    m_favorites = settings->favoriteStations().toSet();
    qDebug() << "favorites:" << m_favorites;
}

bool StationListModel::load(const QString &filename)
{
    QFile file(filename);
    QFileInfo fi(file);

    qDebug() << "loading file:" << fi.absoluteFilePath();

    emit layoutAboutToBeChanged();
    beginResetModel();
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
    qDebug() << rowCount() << "stations loaded";
    if (m_reader.hasError()) {
        qDebug() << "parser error for:" << filename;
        return false;
    } else if (file.error() != QFile::NoError) {
        qDebug() << "file error for:" << filename;
        return false;
    }
    endResetModel();
    emit layoutChanged();
    return true;
}

QHash<int, QByteArray> StationListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[StationListModel::PositionRole] = "position";
    roles[StationListModel::RecentIndicatorRole] = "recent";
    roles[StationListModel::FavoriteIndicatorRole] = "favorite";
    roles[StationListModel::StationCodeRole] = "code";
    roles[StationListModel::LongitudeRole] = "longitude";
    roles[StationListModel::LatitudeRole] = "latitude";
    roles[StationListModel::SectionRole] = "section";
    return roles;
}

int StationListModel::rowCount(const QModelIndex &) const
{
    return m_stations.count();
}

QVariant StationListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() >= m_stations.count()) {
        return QVariant();
    }
    StationItem item = m_stations[index.row()];
    Settings *settings = Settings::instance();
    switch (role) {
    case Qt::DisplayRole:
        return QVariant::fromValue(item.name());
    case PositionRole:
        return QVariant::fromValue(item.position());
    case RecentIndicatorRole:
        return QVariant(settings->recentStations().contains(item.name()));
    case FavoriteIndicatorRole:
        return QVariant(m_favorites.contains(item.name()));
    case StationCodeRole:
        return QVariant::fromValue(item.code());
    case LatitudeRole:
        return QVariant::fromValue(item.position().latitude());
    case LongitudeRole:
        return QVariant::fromValue(item.position().longitude());
    case SectionRole:
        if (m_favorites.contains(item.name()))
            return QVariant::fromValue(tr("Favorites"));
        else
            return QVariant(item.name()[0]);
    default:
        return QVariant::fromValue(QString("Unknown role requested"));
    }
}

bool StationListModel::setData(const QModelIndex &index, QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == FavoriteIndicatorRole) {
        bool favorite = value.toBool();
        if (data(index, FavoriteIndicatorRole) != favorite) {
            QString name =  m_stations[index.row()].name();
            if (favorite) {
                qDebug() << "adding" << name << "to favorites";
                m_favorites.insert(name);
            } else {
                qDebug() << "removing" << name << "from favorites";
                m_favorites.remove(name);
            }
            Settings *settings = Settings::instance();
            settings->setFavoriteStations(QStringList::fromSet(m_favorites));
            QVector<int> changedRoles;
            changedRoles << FavoriteIndicatorRole;
            //emit dataChanged(index, index, changedRoles);
            emit dataChanged(index, index);
        }
        return true;
    }
   return false;
}

Qt::ItemFlags StationListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
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
                skipUnknownElement(m_reader.name().toString());
            }
        } else {
            m_reader.readNext();
        }
    }
}

void StationListModel::readStationElement()
{
    StationItem item;
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_stations.append(item);
            m_reader.readNext();
            break;
        } else if (m_reader.isStartElement()) {
            if (m_reader.name() == "pos") {
                readPosElement(item);
            } else  if (m_reader.name() == "name") {
                readNameElement(item);
            } else  if (m_reader.name() == "code") {
                readCodeElement(item);
            } else {
                skipUnknownElement(m_reader.name().toString());
            }
        } else {
            m_reader.readNext();
        }
    }
}

void StationListModel::readPosElement(StationItem &item)
{
    QStringList coordinates = m_reader.readElementText().split(",");
    QGeoCoordinate pos = QGeoCoordinate(coordinates[0].toDouble(), coordinates[1].toDouble());
    item.setPosition(pos);
    m_reader.readElementText();
    if (m_reader.isEndElement()) {
        m_reader.readNext();
    }
}

void StationListModel::readNameElement(StationItem &item)
{
    item.setName(m_reader.readElementText());
    if (m_reader.isEndElement()) {
        m_reader.readNext();
    }
}

void StationListModel::readCodeElement(StationItem &item)
{
    const QString code = m_reader.readElementText();
    qDebug() << "reading code element" << code;

    item.setCode(code);
    if (m_reader.isEndElement()) {
        m_reader.readNext();
    }
}

void StationListModel::skipUnknownElement(const QString &name)
{
    qDebug() << "skipping unknown element" << name << "at line" << m_reader.lineNumber();

    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        } else if (!m_reader.isStartElement()) {
            skipUnknownElement(m_reader.name().toString());
        } else {
            m_reader.readNext();
        }
    }
}
