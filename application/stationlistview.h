#ifndef STATIONLISTVIEW_H
#define STATIONLISTVIEW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
    class StationListView;
}

class QActionGroup;
class QStringListModel;
class QSortFilterProxyModel;

class StationView;

class StationListView : public QMainWindow
{
    Q_OBJECT

public:
    explicit StationListView(QWidget *parent = 0);
    ~StationListView();

signals:
    void stationSelected(const QString &);

private slots:
    void showSettings(void);
    void showStation(const QModelIndex &index);

private:
    Ui::StationListView *ui;
    QActionGroup *viewSelectionGroup;
    QStringListModel *stationListModel;
    QSortFilterProxyModel *filterModel;
    StationView *stationView;
};

#endif // STATIONLISTVIEW_H
