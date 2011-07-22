import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0

Page {
    property alias html: view.html
    anchors.fill: parent

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; }
    }
    LabelStyle {
        id: labelStyle
    }
    WebView {
        id: view
        anchors.fill: parent
        settings.defaultFontSize: labelStyle.fontPixelSize
        settings.defaultFixedFontSize: labelStyle.fontPixelSize
        settings.standardFontFamily: labelStyle.fontFamily
    }
 }
