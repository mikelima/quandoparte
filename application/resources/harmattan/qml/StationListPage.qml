import QtQuick 1.0
import QtMobility.location 1.1
import com.nokia.meego 1.1
import net.cirulla.quandoparte 1.0
import "uiconstants.js" as UiConstants
import "StationListPage.js" as Private

Page {
    property variant stationView
    id: stationListPage
    tools: ToolBarLayout {
        id: toolBar
        ToolIcon {
            iconId: "icon-m-toolbar-search" + (theme.inverted ? "-white": "")
            onClicked: searchField.open = !searchField.open
        }
        ToolIcon {
            iconId: "icon-m-toolbar-view-menu" + (theme.inverted ? "-white": "")
            onClicked: menu.open()
        }
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
                    checked: settings.autoUpdate
                    onCheckedChanged: settings.autoUpdate = checked
                }
            }
            MenuItem {
                text: qsTr("Use Dark Theme")
                Switch {
                    id: darkThemeSwitchSwitch
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                        rightMargin: UiConstants.DefaultMargin
                    }
                    checked: settings.darkThemePreferred
                    onCheckedChanged: {
                        settings.darkThemePreferred = checked
                        theme.inverted = checked
                    }
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
        open: false
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
    Binding {
        target: stationListView
        property: "section.property"
        value: header.selectedIndex === 0 ? "name" : ""
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
            cacheBuffer: 10
            anchors {
                top: shadow.top
                bottom: parent.bottom
            }
            model:  stationListProxyModel
            section {
                //property: "name"
                criteria: ViewSection.FirstCharacter
                delegate: Item {
                    width: parent.width
                    height: UiConstants.SectionItemHeightSmall
                    anchors {
                        margins: UiConstants.DefaultMargin
                    }
                    Image {
                        anchors {
                            left: parent.left
                            right: sectionLabel.left
                            verticalCenter: parent.verticalCenter
                            margins: UiConstants.DefaultMargin
                        }
                        source: "image://theme/meegotouch-separator-" + (theme.inverted ? "inverted-" : "") + "background-horizontal"
                    }
                    Label {
                        id: sectionLabel
                        anchors {
                            right: sectionRightMargin.left
                            verticalCenter: parent.verticalCenter
                        }
                        text: section
                    }
                    Item {
                        id: sectionRightMargin
                        anchors {
                            right: parent.right
                        }
                        width: UiConstants.DefaultMargin
                        height: UiConstants.DefaultMargin
                    }
                }
            }
            delegate: Item {
                id: listItem
                height: UiConstants.ListItemHeightSmall
                width: parent.width
                BorderImage {
                    id: background
                    anchors.fill: parent
                    // Fill page borders
                    visible: mouseArea.pressed
                    source: "image://theme/meegotouch-list-fullwidth-" + (theme.inverted ? "inverted-" : "") + "background-pressed"
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
                            text: Private.highlightSearch(model.name, UiConstants.AccentColor)
                            font.bold: true
                        }
                    }
                }
                Image {
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    //source: "image://theme/meegotouch-separator-" + (theme.inverted ? "inverted-" : "") + "background-horizontal"
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: background
                    onClicked: {
                        Private.loadStation(model.name, model.code)
                    }
                    onPressAndHold: contextMenu.open()
                }
                ContextMenu {
                    id: contextMenu
                    MenuLayout {
                        MenuItem {
                            text: qsTr("Show on the map")
                            onClicked: Qt.openUrlExternally("geo:" + model.longitude + "," + model.latitude)
                        }
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
