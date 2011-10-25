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

#include "view.h"
#include "settings.h"
#include "dataprovider.h"
#include "stationlistmodel.h"
#include "stationlistproxymodel.h"
#include "stationschedulemodel.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QModelIndex>
#include <QtConcurrentRun>
#include <QtDeclarative>

// search Paths seem to be broken in Harmattan?

static QString trueFilePath(QString path)
{
    qDebug() << "searching for" << path;
    QString searchPathName = path.section(':', 0, 0);
    qDebug() << "path is" << searchPathName;
    QString fileName = path.section(':', 1, 1);
    qDebug() << "filename is" << fileName;
    QStringList dirs = QDir::searchPaths(searchPathName);
    foreach(QString dir, dirs) {
        qDebug() << "searching in" << dir;
       QDir current(dir);
       QString absoluteFileName = current.absoluteFilePath(fileName);
        if (current.exists(fileName)) {
            qDebug() << "found " << fileName << "in path" << absoluteFileName;
            return absoluteFileName;
        }
    }
    qDebug() << "file not found";
    return QString();
}

View::View(QWidget *parent) :
    QDeclarativeView(parent),
    stationListModel(new StationListModel(this)),
    stationListProxyModel(new StationListProxyModel(this))
{
    showFullScreen();
    future = QtConcurrent::run(
                stationListModel, &StationListModel::load,
                trueFilePath("stations:stations.qpl"));

    stationListProxyModel->setSourceModel(stationListModel);

    /* Types to be made accessible to QML */
    qRegisterMetaType<QModelIndex>("QModelIndex");
    qmlRegisterType<Settings>("net.cirulla.quandoparte", 1, 0, "Settings");
    qmlRegisterType<StationListProxyModel>(
                "net.cirulla.quandoparte", 1, 0, "StationListProxyModel");
    qmlRegisterType<StationScheduleModel>(
                "net.cirulla.quandoparte", 1, 0, "StationScheduleModel");

    QDeclarativeContext *context = this->rootContext();
    /* objects to be made accessible to QML */
    context->setContextProperty("settings", Settings::instance());
    context->setContextProperty("stationList", stationListModel);
    context->setContextProperty("stationListProxyModel", stationListProxyModel);

    // This does not seem ot work in harmattan. As a workaround, change dir to
    // the qml dir, then load the file.
    // m_view->setSource(QUrl::fromLocalFile("qml:main.qml"));
    setSource(QUrl::fromLocalFile(trueFilePath("qml:main.qml")));
}

View::~View()
{
    future.waitForFinished();
}
