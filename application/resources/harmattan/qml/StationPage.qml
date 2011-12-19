import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants

Page {
    property alias name: schedule.name

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; }
    }
    PageHeader {
        id: header
        anchors.top: parent.top
        selectedIndex: schedule.type
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
            model:  schedule
            delegate: Item {
                id: listItem
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
                                text: arrivalTime
                                font.bold: UiConstants.SpecialFontBoldness
                                font.pixelSize: UiConstants.SpecialFontPixelSize
                                visible: schedule.type === StationScheduleModel.ArrivalSchedule
                            }
                            Label {
                                text: departureTime
                                font.bold: UiConstants.SpecialFontBoldness
                                font.pixelSize: UiConstants.SpecialFontPixelSize
                                visible: schedule.type === StationScheduleModel.DepartureSchedule
                            }
                            Label {
                                text: train
                                font.bold: UiConstants.SpecialFontBoldness
                                font.pixelSize: UiConstants.SpecialFontPixelSize
                                color: UiConstants.AccentColor
                            }
                        }
                        Label {
                            text: qsTr("from ") + arrivalStation
                            font.bold: UiConstants.DefaultFontBoldness
                            font.pixelSize: UiConstants.DefaultFontPixelSize
                            visible: schedule.type === StationScheduleModel.ArrivalSchedule
                        }
                        Label {
                            text: qsTr("to ") + departureStation
                            font.bold: UiConstants.DefaultFontBoldness
                            font.pixelSize: UiConstants.DefaultFontPixelSize
                            visible: schedule.type === StationScheduleModel.DepartureSchedule
                        }
                        Label {
                            id: delayLabel
                            text: delay
                            font.bold: UiConstants.SubtitleFontBoldness
                            font.pixelSize: UiConstants.SubtitleFontPixelSize
                        }
                    }
                    Label {
                        anchors {
                            bottom: bodyRow.bottom
                            right: bodyRow.right
                            rightMargin: UiConstants.DefaultMargin
                        }
                        text: qsTr("Platform ") + actualPlatform
                        font.bold: UiConstants.SubtitleFontBoldness
                        font.pixelSize: UiConstants.SubtitleFontPixelSize
                    }
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
                    }
                }
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

 }
