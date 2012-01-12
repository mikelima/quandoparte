import QtQuick 1.1
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants

Page {
    property alias name: schedule.name

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop() }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; onClicked: menu.open() }
    }
    PageHeader {
        id: header
        anchors.top: parent.top
        selectedIndex: schedule.type
        options: [
            qsTr("Departures"),
            qsTr("Arrivals")
        ]
    }
    InfoBar {
        id: infoBar
        anchors.top: header.bottom
        text: parent.name
    }
    Binding {
        target: schedule
        property: "type"
        value: header.selectedIndex
    }
    LabelStyle {
        id: labelStyle
    }
    Item {
        id: view
        anchors {
            top: infoBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        DroppedShadow {
            id: shadow
            anchors.top: view.top
        }
        ListView {
            id: stationScheduleView
            clip: true
            visible: false
            width: parent.width
            anchors {
                top: shadow.top
                bottom: parent.bottom
            }
            model: schedule
            delegate: StationScheduleDelegate {
                type: schedule.type
                arrivalTime: model.arrivalTime
                departureTime: model.departureTime
                train: model.train
                arrivalStation: model.arrivalStation
                departureStation: model.departureStation
                delay: model.delay
                actualPlatform: model.actualPlatform
                expectedPlatfrom: model.expectedPlatform
            }
        }
        ScrollDecorator {
            id: decorator
            flickableItem: stationScheduleView
        }
        BusyIndicator {
            id: busyIndicator
            platformStyle: BusyIndicatorStyle {
                size: "large"
            }
            anchors.centerIn: parent
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
    Component.onCompleted: {
        updateTimer.timeout.connect(updateStation)
    }
    function updateStation() {
        schedule.fetch(schedule.name)
    }
}
