import QtQuick 1.1
import com.nokia.meego 1.0


ApplicationWindow {
    showToolBar: true
    showStatusBar: true
    Page {
        id: mainPage
        CheckBox {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    ToolBarLayout {
        id: mainToolBar
    }

}
