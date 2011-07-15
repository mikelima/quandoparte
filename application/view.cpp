#include "view.h"
#include "stationlistmodel.h"
#include "stationlistproxymodel.h"

#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QDebug>
#include <QDir>
#include <QFile>

// search Paths seem to be broken in Harmattan?

static QString trueFilePath(QString path)
{
    qDebug() << "searching for" << path;
    QString searchPathName = path.section(':', 0, 0);
    qDebug() << "path is" << searchPathName;
    QString fileName = path.section(':', 1, 1);
    qDebug() << "filename is" << fileName;
    QStringList dirs = QDir::searchPaths(searchPathName);
    foreach(QString dir, dirs) {
        qDebug() << "searching in" << dir;
       QDir current(dir);
       QString absoluteFileName = current.absoluteFilePath(fileName);
        if (current.exists(fileName)) {
            qDebug() << "found " << fileName << "in path" << absoluteFileName;
            return absoluteFileName;
        }
    }
    qDebug() << "file not found";
    return QString();
}

View::View(QWidget *parent) :
    QDeclarativeView(parent),
    stationListModel(new StationListModel(this)),
    stationListProxyModel(new StationListProxyModel(this))
{
    showFullScreen();
    stationListModel->load(trueFilePath("stations:stations.qpl"));

    stationListProxyModel->setSourceModel(stationListModel);
    stationListProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    QDeclarativeContext *context = this->rootContext();
    context->setContextProperty("stationListProxyModel", stationListProxyModel);

    // This does not seem ot work in harmattan. As a workaround, change dir to
    // the qml dir, then load the file.
    // m_view->setSource(QUrl::fromLocalFile("qml:main.qml"));
    setSource(QUrl::fromLocalFile(trueFilePath("qml:main.qml")));

}
