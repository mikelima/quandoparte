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
                text: qsTr("About Quando Parte")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                text: qsTr("Stations by Name")
                onClicked: stationListProxyModel.sortingMode = StationListProxyModel.AlphaSorting
            }
            MenuItem {
                text: qsTr("Stations by Distance")
                onClicked: stationListProxyModel.sortingMode = StationListProxyModel.DistanceSorting
            }
            MenuItem {
                text: qsTr("Stations Recently Seen")
                onClicked: stationListProxyModel.sortingMode = StationListProxyModel.RecentUsageSorting
            }
        }
        PageHeader {
            id: header
            SearchField {
                id: searchField
                placeholderText: qsTr("Search station...")
                inputMethodHints: Qt.ImhNoAutoUppercase
                onTextChanged: stationListPage.searchPattern = searchField.text
                width: stationListPage.width
                EnterKey.onClicked: searchField.focus = false
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
            objectName:
                    searchField.focus = false
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
                onClicked: {
                    Private.loadStation(model.name, model.code)
                }
                //onPressAndHold: contextMenu.show(listItem)
                menu: contextMenu
                Component {
                    id: contextMenu
                    ContextMenu {
                        MenuItem {
                            text: model.favorite ? qsTr("Remove from Favorites") : qsTr("Add to Favorites")
                            onClicked: {
                                console.log("Favorite Stations (before):" + settings.favoriteStations)
                                model.favorite ^= true
                                /*
                                var index = settings.favoriteStations.indexOf(model.name)
                                if (index === -1)
                                    settings.favoriteStations.push(model.name)
                                else settings.favoriteStations.splice(index, 1)
                                */
                                console.log("Favorite Stations (after):" + settings.favoriteStations)
                            }
                        }
                        MenuItem {
                            text: qsTr("Show on the map")
                            onClicked: Qt.openUrlExternally("geo:" + model.latitude + "," + model.longitude)
                        }
                    }
                }
            }
            VerticalScrollDecorator {}
        }
    }
}
