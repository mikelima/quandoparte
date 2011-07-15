#ifndef QP_VIEW_H
#define QP_VIEW_H

#include <QDeclarativeView>

class StationListModel;
class StationListProxyModel;

class View : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

signals:

public slots:

private:
   StationListModel *stationListModel;
   StationListProxyModel *stationListProxyModel;
};

#endif // QP_VIEW_H
