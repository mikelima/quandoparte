import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: window
    showToolBar: true
    showStatusBar: screen.currentOrientation === Screen.Landscape ? false : true
    initialPage: StationListPage {
    }
    /*
    ToolBar {
        anchors.bottom: parent.bottom
    }*/
}
