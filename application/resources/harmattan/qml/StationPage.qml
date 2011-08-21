import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0

Page {
    property alias html: view.html
    property alias url: view.url
    anchors.fill: parent

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; }
    }
    PageHeader {
        id: header
        anchors.top: parent.top
        selectedIndex: settings.showArrivalsPreferred ? 1 : 0
        options: ListModel {
            id: dialogOptions
            ListElement {
                name: QT_TR_NOOP("Departures")
            }
            ListElement {
                name: QT_TR_NOOP("Arrivals")
            }
        }
    }
    Binding {
        target: settings
        property: "showArrivalsPreferred"
        value: header.selectedIndex === 1 ? true : false
    }
    LabelStyle {
        id: labelStyle
    }
    WebView {
        id: view
        anchors {
            top: header.bottom;
            bottom: parent.bottom;
        }
        width: parent.width

        settings.defaultFontSize: labelStyle.fontPixelSize
        settings.defaultFixedFontSize: labelStyle.fontPixelSize
        settings.standardFontFamily: labelStyle.fontFamily
    }
 }
