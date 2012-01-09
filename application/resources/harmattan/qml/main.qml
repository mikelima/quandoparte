import QtQuick 1.1
import QtMobility.systeminfo 1.2
import com.nokia.meego 1.0

PageStackWindow {
    id: window
    showToolBar: true
    showStatusBar: screen.currentOrientation === Screen.Landscape ? false : true
    initialPage: StationListPage {
    }
    AlignedTimer {
        id: updateTimer
        minimumInterval: 120
        maximumInterval: 130
    }
    Component.onCompleted: {
        if (settings.checkingInterval > 0) updateTimer.start()
    }
}
