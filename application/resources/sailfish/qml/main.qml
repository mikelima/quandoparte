import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0
import "pages"

ApplicationWindow {
    id: window
    initialPage: Qt.resolvedUrl("pages/StationListPage.qml")
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    Timer { /* XXX This is an AlignedTimer in Harmattan, which should be better for battery */
        id: updateTimer
        interval: 120000
        repeat: true
        running: Qt.application.active && settings.autoUpdate
    }
    StationScheduleModel {
        id: schedule
    }
    Component.onCompleted: {
        if (Qt.application.active && settings.autoUpdate) {
            updateTimer.start()
        }
    }
}
