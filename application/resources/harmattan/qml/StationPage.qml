import QtQuick 1.1
import com.nokia.meego 1.1
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants

Page {
    property alias name: schedule.name
    property alias code: schedule.code

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon {
            iconId: "icon-m-toolbar-back" + (theme.inverted ? "-white": "")
            onClicked: pageStack.pop()
        }
        ToolIcon {
            iconId: "icon-m-toolbar-refresh" + (theme.inverted ? "-white": "")
            onClicked: updateStation() }
        ToolIcon {
            iconId: "icon-m-toolbar-view-menu" + (theme.inverted ? "-white": "")
            onClicked: menu.open()
        }
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
            cacheBuffer: 40
            anchors {
                top: shadow.top
                bottom: parent.bottom
            }
            model: schedule
            delegate: StationScheduleDelegate {
                width: stationScheduleView.width
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
            running: visible
        }
        Item {
            id: errorDisplay
            anchors {
                top: shadow.top
                bottom: parent.bottom
            }
            width: parent.width
            opacity: 0.6
            Label {
                textFormat: Text.RichText
                visible: parent.visible
                wrapMode: Text.WordWrap
                text: "<h2>" + qsTr("Error!") + "</h2><p>" + schedule.error + "</p>"
                width: parent.width
                // font.pixelSize: UiConstants.HeaderFontPixelSize
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
            }
            onVisibleChanged: if (visible) console.log("showing error: " + schedule.error)
        }
        states: [
            State {
                name: "loading"
                when: !completed
                PropertyChanges {
                    target: stationScheduleView
                    visible: false
                }
                PropertyChanges {
                    target: errorDisplay
                    visible: false
                }
                PropertyChanges {
                    target: busyIndicator
                    visible: true
                }
            },
            State {
                name: "ready"
                when: completed && schedule.error === ""
                PropertyChanges {
                    target: stationScheduleView
                    visible: true
                }
                PropertyChanges {
                    target: errorDisplay
                    visible: false
                }
                PropertyChanges {
                    target: busyIndicator
                    visible: false
                }
            },
            State {
                name: "error"
                when: schedule.error !== ""
                PropertyChanges {
                    target: stationScheduleView
                    visible: false
                }
                PropertyChanges {
                    target: errorDisplay
                    visible: true
                }
                PropertyChanges {
                    target: busyIndicator
                    visible: false
                }
            }
        ]
    }
    StationScheduleModel {
        id: schedule
        onNameChanged: updateStation()
        onLayoutChanged: if (error) view.state = "error"
                         else view.state = "ready"
    }
    Component.onCompleted: {
        updateTimer.timeout.connect(updateStation)
        view.state = "loading"
    }
    function updateStation() {
        view.state = "loading"
        console.log("Updating station with " + schedule.name + ", " + schedule.code)
        schedule.fetch(schedule.name, schedule.code)
    }
}
