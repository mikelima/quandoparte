import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0
import "components"

Page {
    property alias name: schedule.name
    property alias code: schedule.code

    SilicaFlickable {
        id: view
        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: qsTr("Update Schedule")
                onClicked: updateStation()
            }
            MenuItem {
                text: qsTr("Departures")
                onClicked: schedule.type = StationScheduleModel.DepartureSchedule
            }
            MenuItem {
                text: qsTr("Arrivals")
                onClicked: schedule.type = StationScheduleModel.ArrivalSchedule
            }
        }
        SilicaListView {
            id: stationScheduleView
            anchors.fill: parent
            clip: true
            visible: false
            width: parent.width
            cacheBuffer: 40
            header: PageHeader {
                    id: header
                    title: (schedule.type === StationScheduleModel.DepartureSchedule ? qsTr("Departures from ") : qsTr("Arrivals to ")) + name
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
        BusyIndicator {
            id: busyIndicator
            anchors.centerIn: parent
            running: visible
            size: BusyIndicatorSize.Large
        }
        Item {
            id: errorDisplay
            anchors.centerIn: parent
            Column {
                anchors.centerIn: parent
                spacing: Theme.paddingMedium
                Label {
                    text: qsTr("Error!")
                    width: parent.width
                    font.pixelSize: Theme.fontSizeHuge
                    horizontalAlignment: Text.AlignHCenter
                }
                Label {
                    text: schedule.error
                    width: parent.width
                    font.pixelSize: Theme.fontSizeHuge
                    horizontalAlignment: Text.AlignHCenter
                }
            }
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
                when: schedule.error
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

        function updateStation() {
            view.state = "loading"
            console.log("Updating station with " + schedule.name + ", " + schedule.code)
            schedule.fetch(schedule.name, schedule.code)
        }
        StationScheduleModel {
            id: schedule
            onNameChanged: view.updateStation()
            onLayoutChanged: if (error) view.state = "error"
                             else view.state = "ready"
        }

        Component.onCompleted: {
            updateTimer.triggered.connect(view.updateStation)
            view.state = "loading"
        }
    }
}
