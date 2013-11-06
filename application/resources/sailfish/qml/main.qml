import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow {
    id: window
    initialPage: StationListPage { }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    Timer { /* XXX This is an AlignedTimer in Harmattan, which should be better for battery */
        id: updateTimer
        interval: 120
    }
}
