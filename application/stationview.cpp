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

#include "stationview.h"

#include <QAction>
#include <QActionGroup>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QWebView>

StationView::StationView(QWidget *parent) :
    QMainWindow(parent),
    theStation(""),
    showArrivalsAction(new QAction(tr("Arrivals"), this)),
    showDeparturesAction(new QAction(tr("Departures"), this)),
    showSettingsAction(new QAction(tr("Settings"), this)),
    showStationListSelectAction(new QAction(tr("Change Station"), this)),
    showAboutAction(new QAction(tr("About"), this)),
    viewSelectionGroup(new QActionGroup(this)),
    menuBar(new QMenuBar(this)),
    menu(new QMenu(menuBar)),
    view(new QWebView(this))
{
    showArrivalsAction->setCheckable(true);
    showDeparturesAction->setCheckable(true);
    showDeparturesAction->setChecked(true);
    viewSelectionGroup->addAction(showArrivalsAction);
    viewSelectionGroup->addAction(showDeparturesAction);
    menu->addAction(showDeparturesAction);
    menu->addAction(showArrivalsAction);
    menu->addAction(showStationListSelectAction);
    menu->addAction(showSettingsAction);
    menu->addAction(showAboutAction);
    menuBar->addAction(menu->menuAction());
    setMenuBar(menuBar);
    view->setTextSizeMultiplier(2.0);
    connect(showAboutAction, SIGNAL(triggered()), this, SIGNAL(aboutTriggered()));
    connect(showSettingsAction, SIGNAL(triggered()), this, SIGNAL(settingsTriggered()));
    connect(showStationListSelectAction, SIGNAL(triggered()), this, SIGNAL(stationListSelectTriggered()));
    setCentralWidget(view);
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_Maemo5StackedWindow);
#endif
}

void StationView::setStation(const QString &station)
{
    setWindowTitle(station);
    theStation = station;
}

void StationView::changeView(void)
{
    qDebug() << "View Changed";
    if (showArrivalsAction->isChecked()) {
        qDebug() << "Showing Arrivals";
    } else {
        qDebug() << "Showing Departures";
    }
}

void StationView::setBaseUrl(const QUrl &baseUrl)
{
    theBaseUrl = baseUrl;
}

void StationView::updateView(const QByteArray &page)
{
    qDebug() << page;
    view->setContent(page, "text/html", theBaseUrl);
}
