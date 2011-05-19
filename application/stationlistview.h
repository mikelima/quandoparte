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
class KeyPressForwarder;

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
    void handleFilterChanges(const QString &filter);

private:
    Ui::StationListView *ui;
    QActionGroup *viewSelectionGroup;
    QStringListModel *stationListModel;
    QSortFilterProxyModel *filterModel;
    KeyPressForwarder *keyPressForwarder;
};

#endif // STATIONLISTVIEW_H
