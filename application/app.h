#ifndef APPLICATION_H
#define APPLICATION_H

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

#include <QApplication>
#include <QStringList>

class QTimer;

class DataProvider;
class StationView;
class StationListView;
class StationListModel;

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = 0);
    ~App();

    static QString dataDir(void);

signals:

public slots:
    void queryStation(const QString &station);
    void updateStation();
    void downloadFinished(const QByteArray &data);
    void showAboutDialog(void);
    void showSettingsDialog(void);
    void showStationSelectView(void);
public:
    void saveSettings(void);
    void readSettings(void);
private:
    DataProvider *dataProvider;
    QTimer *checkingTimer;
    StationView *stationView;
    StationListModel *stationListModel;
    StationListView *stationListView;
};

#endif // APPLICATION_H
