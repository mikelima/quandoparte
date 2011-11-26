import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants

Page {
    property alias name: schedule.name
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
        anchors.top: info.bottom
        anchors.bottom: tools.top
        x: 16
        y: 16
        width: parent.width - 32
        height: parent.height

        ListView {
            id: stationScheduleView
            clip: true
            visible: false
            width: parent.width
            height: parent.height
            model:  schedule
            delegate: Item {
                id: listItem
                height: 64
                width: parent.width
                BorderImage {
                    id: background
                    anchors.fill: parent
                    // Fill page borders
                    visible: mouseArea.pressed
                    source: "image://theme/meegotouch-list-background-pressed-center"
                }
                Row {
                    anchors.fill: parent

                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            id: mainText
                            text: train
                            font.bold: true
                        }
                    }
                }
                Image {
                    source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "")
                    anchors.right: parent.right;
                    anchors.verticalCenter: parent.verticalCenter
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: background
                    onClicked: {
                        // Load an external page about the train, for now
                    }
                }
            }
        }
        BusyIndicator {
            id: busyIndicator
            anchors.centerIn: view
            visible: !stationScheduleView.visible
            running: visible
        }
        states: [
            State {
                name: "loading"
                PropertyChanges {
                    target: stationScheduleView
                    visible: false
                }
            },
            State {
                name: "ready"
                PropertyChanges {
                    target: stationScheduleView
                    visible: true
                }
            }
        ]
    }
    StationScheduleModel {
        id: schedule
        onNameChanged: schedule.fetch(name)
        onLayoutChanged: view.state = "ready"
    }

 }
