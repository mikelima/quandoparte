#ifndef STATIONLISTVIEW_H
#define STATIONLISTVIEW_H

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

#include "stationlistproxymodel.h"

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
    class StationListView;
}

class QActionGroup;
class QStringListModel;
class QSortFilterProxyModel;
class KeyPressForwarder;

class StationView;
class StationListModel;
class StationListProxyModel;

QTM_USE_NAMESPACE

class StationListView : public QMainWindow
{
    Q_OBJECT
public:
    explicit StationListView(StationListModel *model, QWidget *parent = 0);
    ~StationListView();

   void setSortingMode(StationListProxyModel::SortingMode mode);
   StationListProxyModel::SortingMode sortingMode(void);

signals:
    void stationSelected(const QString &);
    void aboutTriggered(void);
    void settingsChangeRequested(void);
    void sortingModeChanged(StationListProxyModel::SortingMode mode);

private slots:
    void showStation(const QModelIndex &index);
    void handleFilterChanges(const QString &filter);
    void handleSortingChange(QAction *action);

    void handlefilterClearClick();

    private:
    Ui::StationListView *ui;
    QActionGroup *viewSelectionGroup;
    StationListModel *stationListModel;
    StationListProxyModel *filterModel;
    KeyPressForwarder *keyPressForwarder;
    StationListProxyModel::SortingMode m_sortingMode;
};

#endif // STATIONLISTVIEW_H
