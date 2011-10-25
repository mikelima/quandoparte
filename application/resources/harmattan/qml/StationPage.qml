import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants

Page {
    property alias name: schedule.name
    property alias html: webView.html
    property alias url: webView.url
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
    InfoBar {
        id: info
        anchors.top: header.bottom
        text: parent.name
    }
    Rectangle {
        id: shadow
        width: parent.width
        anchors.top: view.top
        height: 5
        gradient: Gradient {
            GradientStop {color: "#aa000000"; position: 0.0}
            GradientStop {color: "#00000000"; position: 1.0}
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
    Item {
        id: view
        anchors {
            top: info.bottom;
            bottom: parent.bottom;
        }
        width: parent.width

        WebView {
            id: webView
            visible: false
            anchors.fill: parent

            settings.defaultFontSize: labelStyle.fontPixelSize
            settings.defaultFixedFontSize: labelStyle.fontPixelSize
            settings.standardFontFamily: labelStyle.fontFamily
        }
    }

    StationScheduleModel {
        id: schedule
    }

    Component.onCompleted: {
        schedule.fetch(name)
    }
 }
