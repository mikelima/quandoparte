import QtQuick 1.0
import QtMobility.location 1.1
import com.nokia.meego 1.0

Page {
    property variant stationView
    id: stationListPage
    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
        ToolIcon { iconId: "icon-m-toolbar-settings"; onClicked: settingsSheet.open(); }
        ToolIcon { iconId: "icon-m-toolbar-view-menu"; }
    }

    function loadStation()
    {
        var component = Qt.createComponent("StationPage.qml");
        if (component.status == Component.Ready) {
            var view = component.createObject(stationListPage)
            stationListPage.stationView = view
            pageStack.push(view)
            view.html = "<h1>Hello World</h1><p>Lorem ipsum</p>"
        }
        else
            console.log('Cannot load component: ' + component.errorString());
    }

    function highlightSearch(s)
    {
        return s.replace(searchField.text,
                         '<span style="text-decoration:underline">' +
                         searchField.text + '</span>')
    }

    Column {
        width: parent.width
        height: parent.height
        TextField {
            id: searchField
            width: parent.width
            placeholderText: "Search..."
            platformStyle: TextFieldStyle { paddingRight: clearButton.width }
            onTextChanged: {
            }
            Image {
                id: clearButton
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-m-input-clear"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        inputContext.reset()
                        searchField.text = ""
                    }
                }
            }
        }
        Rectangle {
            height: 16
        }
        ListView {
            id: stationListView
            clip: true
            width: parent.width
            height: parent.height
            model:  stationListProxyModel
            /*
            model: ListModel {
                id: model
                ListElement {
                    name: "Genova Voltri"
                }
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
                    name: "Genova Via di Francia"
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
            }*/
            delegate: Item {
                id: listItem
                height: 48
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
                            text: highlightSearch(model.display)
                            font.bold: true
                        }
                    }
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: background
                    onClicked: {
                        stationListPage.loadStation(model.display)
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
}

