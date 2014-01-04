import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0
import "StationListPage.js" as Private

Page {
    id: stationListPage
    property variant stationView
    property string searchPattern
    Binding {
        target: stationListProxyModel
        property: "searchPattern"
        value: stationListPage.searchPattern
    }
    SilicaFlickable {
        interactive: !stationListView.flicking
        anchors.fill: parent
        pressDelay: 0
        PullDownMenu {
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
            MenuItem {
                text: qsTr("Show Stations by Name")
                onClicked: stationListProxyModel.sortingMode = StationListProxyModel.AlphaSorting
                font.italic: (stationListProxyModel.sortingMode === StationListProxyModel.AlphaSorting)
                enabled: (stationListProxyModel.sortingMode !== StationListProxyModel.AlphaSorting)
            }
            MenuItem {
                text: qsTr("Show Stations by Distance")
                onClicked: stationListProxyModel.sortingMode = StationListProxyModel.DistanceSorting
                font.italic: (stationListProxyModel.sortingMode === StationListProxyModel.DistanceSorting)
                enabled: (stationListProxyModel.sortingMode !== StationListProxyModel.DistanceSorting)
            }
            MenuItem {
                text: qsTr("Show Recent Stations")
                onClicked: stationListProxyModel.sortingMode = StationListProxyModel.RecentUsageSorting
                font.italic: (stationListProxyModel.sortingMode === StationListProxyModel.RecentUsageSorting)
                enabled: (stationListProxyModel.sortingMode !== StationListProxyModel.RecentUsageSorting)
            }
        }
        PageHeader {
            id: header
            SearchField {
                id: searchField
                placeholderText: qsTr("Search station...")
                inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
                onTextChanged: stationListPage.searchPattern = searchField.text
                width: stationListPage.width
                EnterKey.onClicked: searchField.focus = false
                EnterKey.iconSource: "image://theme/icon-m-enter-close"
            }
        }
        SilicaListView {
            id: stationListView
            clip: true
            width: parent.width
            cacheBuffer: 4 * Theme.itemSizeExtraSmall
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            model:  stationListProxyModel
            delegate: ListItem {
                id: listItem
                contentHeight: Theme.itemSizeExtraSmall
                width: parent.width
                Label {
                    id: mainText
                    anchors {
                        fill: parent
                        margins: Theme.paddingMedium
                    }
                    x: Theme.paddingLarge
                    textFormat: Text.StyledText
                    text: model.name ? Private.highlightSearch(model.name, Theme.highlightColor) : ""
                    verticalAlignment: Text.AlignVCenter
                }
                Image {
                    id: favoriteIndicator
                    visible: model.favorite
                    source: "image://theme/icon-m-favorite-selected"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                }
                menu: contextMenu
                Component {
                    id: contextMenu
                    ContextMenu {
                        MenuItem {
                            text: model.favorite ? qsTr("Remove from Favorites") : qsTr("Add to Favorites")
                            onClicked: {
                                model.favorite ^= true
                                console.log("Favorite Stations:" + settings.favoriteStations)
                            }
                        }
                        MenuItem {
                            text: qsTr("Show on the map")
                            onClicked: Qt.openUrlExternally("geo:" + model.latitude + "," + model.longitude)
                        }
                    }
                }
                onPressed: searchField.focus = false
                onClicked: Private.loadStation(model.name, model.code)
            }
            VerticalScrollDecorator {}
        }
    }
}
