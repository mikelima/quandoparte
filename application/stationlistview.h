#ifndef STATIONLISTVIEW_H
#define STATIONLISTVIEW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QGeoPositionInfoSource>

namespace Ui {
    class StationListView;
}

class QActionGroup;
class QStringListModel;
class QSortFilterProxyModel;
class KeyPressForwarder;

class StationView;
class StationListModel;

QTM_USE_NAMESPACE

class StationListView : public QMainWindow
{
    Q_OBJECT

public:
    explicit StationListView(StationListModel *model, QWidget *parent = 0);
    ~StationListView();

signals:
    void stationSelected(const QString &);
    void aboutTriggered(void);

public slots:
    void updatePosition(const QGeoPositionInfo &update);

private slots:
    void showSettings(void);
    void showStation(const QModelIndex &index);
    void handleFilterChanges(const QString &filter);

private:
    Ui::StationListView *ui;
    QActionGroup *viewSelectionGroup;
    StationListModel *stationListModel;
    QSortFilterProxyModel *filterModel;
    KeyPressForwarder *keyPressForwarder;
};

#endif // STATIONLISTVIEW_H
