import QtQuick 2.0
import QtWebKit 3.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0

BackgroundItem {
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
    property bool compact: false
    property int mainFontSize: compact ? Theme.fontSizeExtraSmall : Theme.fontSizeMedium
    property int smallFontSize: compact ? Theme.fontSizeExtraSmall : Theme.fontSizeSmall

    implicitHeight: Theme.paddingMedium * 2 + firstRow.height + secondRow.height + thirdRow.height
    height: implicitHeight
    Item {
        id: bodyRow
        anchors {
            fill: parent
            margins: Theme.paddingSmall
        }
        DelayIndicator {
            id: indicator
            level: delayClass
            height: root.height
        }
        Item {
            id: mainMatter
            anchors {
                left: indicator.right
                right: bodyRow.right
                leftMargin: Theme.paddingMedium
            }
            Row {
                id: firstRow
                height: mainFontSize
                anchors.top: parent.top
                spacing: Theme.paddingMedium
                Label {
                    id: arrivalTimeLabel
                    font.pixelSize: mainFontSize
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    id: departureTimeLabel
                    font.pixelSize: mainFontSize
                    visible: type === StationScheduleModel.DepartureSchedule
                }
                Label {
                    id: trainLabel
                    font.pixelSize: mainFontSize
                    color: Theme.highlightColor
                }
            }
            Row {
                id: secondRow
                height: mainFontSize
                anchors.top: firstRow.bottom
                Label {
                    text: qsTr("from <font color='%2'>%1</font>").arg(root.arrivalStation).arg(Theme.primaryColor)
                    textFormat: Text.StyledText
                    wrapMode: Text.Wrap
                    font.pixelSize: mainFontSize
                    color: Theme.secondaryColor
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    text: qsTr("to <font color='%2'>%1</font>").arg(root.departureStation).arg(Theme.primaryColor)
                    textFormat: Text.StyledText
                    wrapMode: Text.Wrap
                    font.pixelSize: mainFontSize
                    color: Theme.secondaryColor
                    visible: type === StationScheduleModel.DepartureSchedule
                }
            }
            Item {
                id: thirdRow
                height: smallFontSize
                anchors {
                    top: secondRow.bottom
                    left: parent.left
                    right: parent.right
                }
                Label {
                    id: delayLabel
                    font.pixelSize: smallFontSize
                    color: Theme.secondaryColor
                }
                Label {
                    anchors {
                        top: parent.top
                        right: parent.right
                        rightMargin: Theme.paddingMedium
                    }
                    text: displayPlatform(root.expectedPlatfrom, root.actualPlatform)
                    font.pixelSize: smallFontSize
                    textFormat: Text.RichText
                    color: Theme.secondaryColor
                    visible: !compact
                }
            }
        }
    }
    onClicked: {
        // Load an external page about the train, for now
        Qt.openUrlExternally(settings.queryBaseUrl + "/" + detailsUrl)
        console.log(settings.queryBaseUrl + "/" + detailsUrl)
    }
    function displayPlatform(expected, actual)
    {
        if (actual === "--") {
            return qsTr("Platform %1").arg(expected)
        } else if (actual === expected || expected === "--") {
            return qsTr("Platform <span style='font-weight:bold;color:%2'>%1</span>").arg(actual).arg("#0f0")
        } else {
            return qsTr("Platform " +
                        "<span style='text-decoration:line-through'>%1</span> " +
                        "<span style='font-weight:bold;color:%3'>%2</span>").arg(expected).arg(actual).arg("#f00")
        }
    }
}
