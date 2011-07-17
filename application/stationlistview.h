#ifndef STATIONLISTVIEW_H
#define STATIONLISTVIEW_H

#include "stationlistproxymodel.h"

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

public slots:
    void updatePosition(const QGeoPositionInfo &update);

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
    QGeoPositionInfoSource *positionInfoSource;
    StationListProxyModel::SortingMode m_sortingMode;
};

#endif // STATIONLISTVIEW_H
