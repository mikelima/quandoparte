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
    SilicaListView {
        id: stationListView
        clip: true
        width: parent.width
        cacheBuffer: 10
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        model:  stationListProxyModel
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
        header: SearchField {
            id: searchField
            placeholderText: qsTr("Search station...")
            inputMethodHints: Qt.ImhNoAutoUppercase
            onTextChanged: stationListPage.searchPattern = searchField.text
            width: stationListPage.width
        }
        delegate: BackgroundItem {
            id: listItem
            height: Theme.itemSizeExtraSmall
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
            onClicked: Private.loadStation(model.name, model.code)
            onPressAndHold: contextMenu.show(listItem)
            ContextMenu {
                id: contextMenu
                MenuItem {
                    text: qsTr("Show on the map")
                    onClicked: Qt.openUrlExternally("geo:" + model.longitude + "," + model.latitude)
                }
            }
        }
    }
}
