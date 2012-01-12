import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants

Item {
    id: root
    property variant type
    property alias arrivalTime: arrivalTimeLabel.text
    property alias departureTime: departureTimeLabel.text
    property alias train: trainLabel.text
    property string arrivalStation
    property string departureStation
    property alias delay: delayLabel.text
    property string actualPlatform
    property string expectedPlatfrom

    height: UiConstants.ListItemHeightDefault
    width: parent.width
    BorderImage {
        id: background
        anchors.fill: parent
        // Fill page borders
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list-background-pressed-center"
    }
    Row {
        id: bodyRow
        anchors.fill: parent
        spacing: UiConstants.ButtonSpacing
        DelayIndicator {
            level: delayClass
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            Row {
                spacing: UiConstants.ButtonSpacing
                Label {
                    id: arrivalTimeLabel
                    font.bold: UiConstants.SpecialFontBoldness
                    font.pixelSize: UiConstants.SpecialFontPixelSize
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    id: departureTimeLabel
                    font.bold: UiConstants.SpecialFontBoldness
                    font.pixelSize: UiConstants.SpecialFontPixelSize
                    visible: type === StationScheduleModel.DepartureSchedule
                }
                Label {
                    id: trainLabel
                    font.bold: UiConstants.SpecialFontBoldness
                    font.pixelSize: UiConstants.SpecialFontPixelSize
                    color: UiConstants.AccentColor
                }
            }
            Label {
                text: qsTr("from ") + root.arrivalStation
                font.bold: UiConstants.DefaultFontBoldness
                font.pixelSize: UiConstants.DefaultFontPixelSize
                visible: type === StationScheduleModel.ArrivalSchedule
            }
            Label {
                text: qsTr("to ") + root.departureStation
                font.bold: UiConstants.DefaultFontBoldness
                font.pixelSize: UiConstants.DefaultFontPixelSize
                visible: type === StationScheduleModel.DepartureSchedule
            }
            Label {
                id: delayLabel
                font.bold: UiConstants.SubtitleFontBoldness
                font.pixelSize: UiConstants.SubtitleFontPixelSize
            }
        }
    }
    Label {
        anchors {
            bottom: bodyRow.bottom
            right: bodyRow.right
            rightMargin: UiConstants.DefaultMargin
        }
        text: qsTr("Platform ") + root.actualPlatform
        font.bold: UiConstants.SubtitleFontBoldness
        font.pixelSize: UiConstants.SubtitleFontPixelSize
    }
    Image {
        anchors {
            left: parent.left
            right: parent.right
        }
        source: "image://theme/meegotouch-separator-background-horizontal"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: background
        onClicked: {
            // Load an external page about the train, for now
            Qt.openUrlExternally(settings.queryBaseUrl + "/" + detailsUrl)
            console.log(settings.queryBaseUrl + "/" + detailsUrl)
        }
    }
}
