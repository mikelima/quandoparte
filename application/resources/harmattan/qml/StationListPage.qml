import QtQuick 1.0
import com.nokia.meego 1.0
import "/usr/lib/qt4/imports/com/nokia/meego/UIConstants.js" as UiConstants

Page {
    id: stationListPage
    tools: toolBar
    anchors.margins: UiConstants.DEFAULT_MARGIN
    Column {
        TextField {
            placeholderText: "Search..."
        }
        ListView {
            id: stationListView
            anchors.fill: parent
            model: ListModel {
                ListElement {
                    name: "Genova Sestri Ponente"
                }
                ListElement {
                    name: "Genova Cornigliano"
                }
                ListElement {
                    name: "Genova Sampierdarena"
                }
                ListElement {
                    name: "Genova Piazza Principe"
                }
                ListElement {
                    name: "Genova Brignole"
                }
                ListElement {
                    name: "Genova Sturla"
                }
                ListElement {
                    name: "Genova Quinto"
                }
                ListElement {
                    name: "Genova Nervi"
                }
            }
            delegate: Item {
                id: listItem
                height: 88
                width: parent.width
                BorderImage {
                    id: background
                    anchors.fill: parent
                    // Fill page borders
                    visible: mouseArea.pressed
                    source: "image://theme/meegotouch-list-background-pressed-center"
                }
                Row {
                    anchors.fill: parent

                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            id: mainText
                            text: model.name
                            //font.family: UiConstants.FONT_FAMILY
                            //font.pixelSize: UiConstants.FONT_DEFAULT
                        }
                    }
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: background
                    onClicked: {
                        stationListPage.openFile(page)
                    }
                }
            }
        }
    }

    Sheet {
        id: settingsSheet
        acceptButtonText: "Save"
        rejectButtonText: "Cancel"
        content: Item {
            x: 16
            y: 16
            width: parent.width - 32
            height: parent.height - 32
            Column {
                spacing: 16
                anchors.fill: parent
                Row {
                    height: 40
                    spacing: 16
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Label {
                        font.bold: true
                        text: "Show Last Station on Startup"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Switch {
                        anchors.verticalCenter: parent.verticalCenter
                        id: showLastStationSwitch
                        anchors.right: parent.right
                    }
                }
                Row {
                    height: 40
                    spacing: 16
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Label {
                        font.bold: true
                        text: "Update Display Periodically"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Switch {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        id: periodicCheckSwitch
                    }
                }
            }
        }
    }

    ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
        ToolIcon { iconId: "icon-m-toolbar-settings"; onClicked: settingsSheet.open(); }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; }
    }
}

