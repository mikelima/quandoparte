import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0
import "StationListPage.js" as Private

Page {
    property variant stationView
    id: stationListPage
    Binding {
        target: stationListProxyModel
        property: "searchPattern"
        value: searchField.text
    }
    Binding {
        target: stationListProxyModel
        property: "sortingMode"
        value: header.currentIndex
    }
    Binding {
        target: stationListView
        property: "section.property"
        value: header.currentIndex === 0 ? "name" : ""
    }
    SilicaListView {
        id: stationListView
        clip: true
        width: parent.width
        cacheBuffer: 10
        anchors.fill: parent
        model:  stationListProxyModel
        header: Column {
            ComboBox {
                id: header
                currentIndex: stationListProxyModel.sortingMode
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("by Name")
                    }
                    MenuItem {
                        text: qsTr("by Distance")
                    }
                    MenuItem {
                        text: qsTr("Recently Seen")
                    }
                }
                label: qsTr("Stations")
            }
            SearchField {
                id: searchField
                placeholderText: qsTr("Search station...")
            }
        }
        section {
            criteria: ViewSection.FirstCharacter
            delegate: Item {
                width: parent.width
                height: Theme.itemSizeSmall
                anchors {
                    margins: Theme.paddingMedium
                }
		Image {
		    anchors {
			left: parent.left
			right: sectionLabel.left
			verticalCenter: parent.verticalCenter
			margins: Theme.paddingMedium
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
                    width: Theme.paddingMedium
                    height: Theme.paddingMedium
                }
            }
            delegate: BackgroundItem {
                id: listItem
                height: Theme.itemSizeSmall
                width: parent.width
                Label {
                    id: mainText
                    x: Theme.paddingLarge
                    text: Private.highlightSearch(model.name, Theme.highlightColor)
                }
                onClicked: Private.loadStation(model.name, model.code)
            }
        }
    }
    ScrollDecorator {
        id: decorator
        flickable: stationListView
    }
}
