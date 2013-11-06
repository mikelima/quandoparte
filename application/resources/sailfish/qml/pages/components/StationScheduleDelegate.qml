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

    implicitHeight: Theme.itemSizeExtraLarge
    height: Theme.itemSizeExtraLarge
    Item {
        id: bodyRow
        anchors {
            fill: parent
            margins: Theme.paddingSmall
        }
        DelayIndicator {
            id: indicator
            level: delayClass
        }
        Item {
            anchors {
                left: indicator.right
                right: bodyRow.right
                leftMargin: Theme.paddingMedium
            }
            Row {
                id: firstRow
                anchors.top: parent.top
                spacing: Theme.paddingMedium
                Label {
                    id: arrivalTimeLabel
                    font.pixelSize: Theme.fontSizeMedium
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    id: departureTimeLabel
                    font.pixelSize: Theme.fontSizeMedium
                    visible: type === StationScheduleModel.DepartureSchedule
                }
                Label {
                    id: trainLabel
                    font.pixelSize: Theme.fontSizeMedium
                    color: Theme.highlightColor
                }
            }
            Item {
                id: secondRow
                height: Theme.fontSizeMedium
                anchors.top: firstRow.bottom
                Label {
                    text: qsTr("from %1").arg(root.arrivalStation)
                    font.pixelSize: Theme.fontSizeMedium
                    visible: type === StationScheduleModel.ArrivalSchedule
                }
                Label {
                    text: qsTr("to %1").arg(root.departureStation)
                    font.pixelSize: Theme.fontSizeMedium
                    visible: type === StationScheduleModel.DepartureSchedule
                }
            }
            Item {
                height: Theme.fontSizeSmall
                anchors {
                    top: secondRow.bottom
                    left: parent.left
                    right: parent.right
                }
                Label {
                    id: delayLabel
                    anchors.top: parent.top
                    font.pixelSize: Theme.fontSizeSmall
                }
                Label {
                    anchors {
                        top: parent.top
                        right: parent.right
                        rightMargin: Theme.paddingMedium
                    }
                    text: displayPlatform(root.expectedPlatfrom, root.actualPlatform)
                    font.pixelSize: Theme.fontSizeSmall
                    textFormat: Text.RichText
                }
            }
        }
    }
    Separator {
        anchors {
            left: parent.left
            right: parent.right
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
