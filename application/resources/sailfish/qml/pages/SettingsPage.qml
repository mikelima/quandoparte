import QtQuick 2.0
import Sailfish.Silica 1.0
import net.cirulla.quandoparte 1.0

Page {
    RemorsePopup {
        id: remorse
    }
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height
        contentWidth: parent.width
        VerticalScrollDecorator {}
        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Settings")
            }
            TextSwitch {
                id: periodicActivation
                text: qsTr("Check Periodically")
                description: qsTr("Update the situation periodically while the station schedule is shown.")
                onCheckedChanged: settings.autoUpdate = checked
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Clear Recent Stations")
                onClicked: remorse.execute(qsTr("Clearing Preferred Stations"), function() {settings.recentStations = ""})
            }
            SectionHeader {
                text: qsTr("Information")
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("About Quando Parte")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }
    }
    Component.onCompleted: {
        periodicActivation.checked = settings.autoUpdate
    }
}
