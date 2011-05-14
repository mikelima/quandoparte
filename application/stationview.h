#ifndef STATIONVIEW_H
#define STATIONVIEW_H

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
    void settingsTriggered(void);
    void stationListSelectTriggered(void);
    void showingArrivalsChanged(bool);

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
