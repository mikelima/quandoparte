#ifndef QP_VIEW_H
#define QP_VIEW_H

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
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtQuick/QQuickView>
#else
#include <QDeclarativeView>
#endif

class StationListModel;
class StationListProxyModel;

class View :
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        public QQuickView
#else
        public QDeclarativeView
#endif
{
    Q_OBJECT
public:
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    explicit View(QWindow *parent = 0);
#else
    explicit View(QWidget *parent = 0);
#endif

    ~View();

signals:

public slots:

private:
    QFuture<void> future;
    StationListModel *stationListModel;
    StationListProxyModel *stationListProxyModel;
};

#endif // QP_VIEW_H
