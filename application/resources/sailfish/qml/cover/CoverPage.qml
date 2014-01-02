import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0
import "../pages/components"

CoverBackground {
    CoverPlaceholder {
        anchors.fill: parent
        text: qsTr("Quando Parte")
        icon.source: "/usr/share/icons/hicolor/86x86/apps/quandoparte.png"
        visible: stationScheduleView.count === 0
    }
    SilicaListView {
        id: stationScheduleView
	anchors.fill: parent
        model: schedule
        delegate: StationScheduleDelegate {
            width: stationScheduleView.width
            compact: true
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
    OpacityRampEffect {
        id: effect
        slope: 2
        offset: 0.5
        sourceItem: stationScheduleView
    }
    CoverActionList {
        enabled: schedule.name.length !== 0
        iconBackground: true
        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: schedule.fetch(schedule.name, schedule.code)
        }
    }
}
