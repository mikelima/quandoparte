import QtQuick 1.0
import QtMobility.location 1.1
import com.nokia.meego 1.0
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants
import "StationListPage.js" as Private

Page {
    property variant stationView
    id: stationListPage
    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-search"; onClicked: searchField.visible = !searchField.visible; }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; onClicked: menu.open() }
    }
    Menu {
        id: menu
        content: MenuLayout {
            MenuItem {
                text: qsTr("Update Periodically")
                Switch {
                    id: periodicCheckSwitch
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                        rightMargin: UiConstants.DefaultMargin
                    }
                    onCheckedChanged: settings.autoUpdate = checked
                }
            }
            MenuItem {
                text: qsTr("About Quando Parte")
                onClicked: Private.showAboutPage()
            }
            Component.onCompleted: periodicCheckSwitch.checked = settings.autoUpdate
        }
    }
    PageHeader {
        id: header
        anchors.top: parent.top
        selectedIndex: stationListProxyModel.sortingMode
        options: [
            qsTr("Stations by Name"),
            qsTr("Stations by Distance"),
            qsTr("Stations Recently Seen")
        ]
    }
    SearchBar {
        id: searchField
        anchors.top: header.bottom
        visible: false
    }
    Binding {
        target: stationListProxyModel
        property: "searchPattern"
        value: searchField.text
    }
    Binding {
        target: stationListProxyModel
        property: "sortingMode"
        value: header.selectedIndex
    }
    Item {
        id: mainView
        anchors {
            top: searchField.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        DroppedShadow {
            id: shadow
            anchors.top: mainView.top
        }
        ListView {
            id: stationListView
            clip: true
            width: parent.width
            anchors {
                top: shadow.top
                bottom: parent.bottom
            }
            model:  stationListProxyModel
            delegate: Item {
                id: listItem
                height: UiConstants.ListItemHeightSmall
                width: parent.width
                BorderImage {
                    id: background
                    anchors.fill: parent
                    // Fill page borders
                    visible: mouseArea.pressed
                    source: "image://theme/meegotouch-list-fullwidth-background-pressed"
                }
                Row {
                    anchors.fill: parent
                    Item {
                        width: UiConstants.DefaultMargin
                        height: UiConstants.DefaultMargin
                    }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            id: mainText
                            text: Private.highlightSearch(model.display, UiConstants.AccentColor)
                            font.bold: true
                        }
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
                        Private.loadStation(model.display)
                    }
                }
            }
        }
        ScrollDecorator {
            id: decorator
            flickableItem: stationListView
        }
    }
}

