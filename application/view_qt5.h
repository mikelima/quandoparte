#ifndef QP_VIEW_QT5_H
#define QP_VIEW_QT5_H

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

#include <QtGlobal>
#include <QFuture>
#include <QtQuick/QQuickView>

class StationListModel;
class StationListProxyModel;

class View :
        public QQuickView
{
    Q_OBJECT
public:
    explicit View(QWindow *parent = 0);

    ~View();

signals:

public slots:

private:
    QFuture<void> future;
    StationListModel *stationListModel;
    StationListProxyModel *stationListProxyModel;
};

#endif // QP_VIEW_QT5_H
