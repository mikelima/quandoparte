import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0
import "components"

Page {
    SilicaFlickable {
        id: view
        pressDelay: 0
        anchors.fill: parent

        function updateStation() {
            view.state = "loading"
            console.log("Updating station with " + schedule.name + ", " + schedule.code)
            schedule.fetch(schedule.name, schedule.code)
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Update Schedule")
                onClicked: view.updateStation()
            }
            MenuItem {
                text: (schedule.type === StationScheduleModel.ArrivalSchedule ?
                          qsTr("Show Departures") :
                          qsTr("Show Arrivals"))
                onClicked: (schedule.type = schedule.type === StationScheduleModel.ArrivalSchedule ?
                               StationScheduleModel.DepartureSchedule :
                               StationScheduleModel.ArrivalSchedule)
            }
            MenuLabel {
                text: (schedule.type === StationScheduleModel.DepartureSchedule ? qsTr("Departures") : qsTr("Arrivals"))
            }
        }
        PageHeader {
            id: header
            title: schedule.name
        }
        SilicaListView {
            id: stationScheduleView
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            clip: true
            visible: false
            width: parent.width
            cacheBuffer: 4 * Theme.itemSizeExtraLarge
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
            ViewPlaceholder {
                enabled: stationScheduleView.count === 0
                text: qsTr("No trains are scheduled at this time")
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
            anchors.fill: parent
            Column {
                anchors.fill: parent
                spacing: Theme.paddingLarge
                Label {
                    textFormat: Text.StyledText
                    wrapMode: Text.WordWrap
                    text: "<p>" + qsTr("Error!") + "</p><p>" + schedule.error + "</p>"
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
            State  {
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

        Connections {
            target: schedule
            onLayoutChanged: if (schedule.error) view.state = "error"
                             else view.state = "ready"
        }
        Component.onCompleted: {
            updateTimer.triggered.connect(view.updateStation)
            view.state = "loading"
        }
        VerticalScrollDecorator {}
    }
}
