#ifndef STATIONVIEW_H
#define STATIONVIEW_H

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

#include <QMainWindow>
#include <QUrl>

class QAction;
class QActionGroup;
class QWebView;

class StationView : public QMainWindow
{
    Q_OBJECT
public:
    explicit StationView(QWidget *parent = 0);

    void setStation(const QString &station);
    void setBaseUrl(const QUrl &theBaseUrl);

signals:
    void aboutTriggered(void);
    void settingsChangeRequested(void);
    void stationListSelectTriggered(void);

public slots:
    void updateView(const QByteArray &page);

private slots:
    void changeView(void);
    void viewSelectionGroupTriggered(QAction *);

private:
    void updateCss(void);

private:
    QString theStation;
    QUrl theBaseUrl;
    QAction *showArrivalsAction;
    QAction *showDeparturesAction;
    QAction *showSettingsAction;
    QAction *showStationListSelectAction;
    QAction *showAboutAction;
    QActionGroup *viewSelectionGroup;
    QMenuBar *menuBar;
    QMenu *menu;
    QWebView *view;
};

#endif // STATIONVIEW_H
