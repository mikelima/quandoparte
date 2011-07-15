import QtQuick 1.1
import com.nokia.meego 1.0
import QtWebKit 1.0

Page {
    property string html: "<p>Hello</p>"
    anchors.fill: parent

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; }
    }
    WebView {
        id: view
        anchors.fill: parent
    }
}
