import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.1
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

    implicitHeight: UiConstants.ListItemHeightLarge
    height: UiConstants.ListItemHeightLarge
    BorderImage {
        id: background
        anchors.fill: parent
        // Fill page borders
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list-fullwidth-" + (theme.inverted ? "inverted-" : "") + "background-pressed"
    }
    Item {
        id: bodyRow
        anchors {
            fill: parent
            margins: UiConstants.ButtonSpacing
        }
        DelayIndicator {
            id: indicator
            anchors {
                top: parent.top
                left: parent.left
            }
            level: delayClass
        }
        Item {
            anchors {
                left: indicator.right
                right: bodyRow.right
                margins: UiConstants.ButtonSpacing
            }
            height: UiConstants.TitleFontPixelSize
            Row {
                id: firstRow
                anchors.top: parent.top
                spacing: UiConstants.ButtonSpacing
                Label {
                    id: arrivalTimeLabel
                    font.bold: UiConstants.TitleFontBoldness
                    font.pixelSize: UiConstants.TitleFontPixelSize
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    id: departureTimeLabel
                    font.bold: UiConstants.TitleFontBoldness
                    font.pixelSize: UiConstants.TitleFontPixelSize
                    visible: type === StationScheduleModel.DepartureSchedule
                }
                Label {
                    id: trainLabel
                    font.bold: UiConstants.TitleFontBoldness
                    font.pixelSize: UiConstants.TitleFontPixelSize
                    color: UiConstants.AccentColor
                }
            }
            Item {
                id: secondRow
                height: UiConstants.DefaultFontPixelSize
                anchors.top: firstRow.bottom
                Label {
                    text: qsTr("from %1").arg(root.arrivalStation)
                    font.bold: UiConstants.DefaultFontBoldness
                    font.pixelSize: UiConstants.DefaultFontPixelSize
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    text: qsTr("to %1").arg(root.departureStation)
                    font.bold: UiConstants.DefaultFontBoldness
                    font.pixelSize: UiConstants.DefaultFontPixelSize
                    visible: type === StationScheduleModel.DepartureSchedule
                }
            }
            Item {
                height: UiConstants.SubtitleFontPixelSize
                anchors {
                    top: secondRow.bottom
                    left: parent.left
                    right: parent.right
                }
                Label {
                    id: delayLabel
                    anchors.top: parent.top
                    font.bold: UiConstants.SubtitleFontBoldness
                    font.pixelSize: UiConstants.SubtitleFontPixelSize
                }
                Label {
                    anchors {
                        top: parent.top
                        right: parent.right
                        rightMargin: UiConstants.DefaultMargin
                    }
                    text: displayPlatform(root.expectedPlatfrom, root.actualPlatform)
                    font.bold: UiConstants.SubtitleFontBoldness
                    font.pixelSize: UiConstants.SubtitleFontPixelSize
                }
            }
        }
    }
    Image {
        anchors {
            leftMargin: UiConstants.DefaultMargin
            rightMargin: UiConstants.DefaultMargin
            left: parent.left
            right: parent.right
        }
        source: "image://theme/meegotouch-separator-"+ (theme.inverted ? "inverted-" : "") + "background-horizontal"
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
    function displayPlatform(expected, actual)
    {
        if (actual === "--") {
            return qsTr("Platform %1").arg(expected)
        } else if (actual === expected || expected === "--") {
            return qsTr("Platform <span style='font-weight:bold;color:%2'>%1</span>").arg(actual).arg(theme.inverted ? "#0f0" : "#080")
        } else {
            return qsTr("Platform " +
                        "<span style='text-decoration:line-through'>%1</span> " +
                        "<span style='font-weight:bold;color:%3'>%2</span>").arg(expected).arg(actual).arg(theme.inverted ? "#f00" : "#800")
        }
    }
}
