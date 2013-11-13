import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        anchors.fill: parent
        anchors.margins: Theme.paddingLarge
        PageHeader {
            id: header
            anchors.top: parent.top
            title: qsTr("About Quando Parte")
        }

        Row {
            anchors.top: header.bottom
            id: firstSection
            spacing: Theme.paddingLarge
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "/usr/share/icons/hicolor/meegotouch/apps/quandoparte.png"
            }
            Label {
                textFormat: Text.RichText
                text: "<style>a:link{color:" + Theme.highlightColor + ";text-decoration:none}</style>" +
                      "<div style='font-size:large;font-weight:bold'><a href='http://quandoparte.garage.maemo.org'>" +
                      qsTr("Quando Parte") + "</a></div>" + "<div style='font-size:small;'>" +
                      qsTr("version ") + settings.versionString + "</div>"
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
        Label {
            anchors {
                top: firstSection.bottom;
                left: parent.left;
                right: parent.right;
                topMargin: Theme.paddingLarge
            }
            fontSizeMode: Text.Fit
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            linkColor: Theme.highlightColor
            text: "<style>a:link{color:" + Theme.highlightColor + ";text-decoration:none}</style>" +
                  "<div style='font-size:small'>" +
                  qsTr("<p>Copyright (c) 2010, 2011, 2012, 2013</p>" +
                       "<p>Luciano Montanaro " +
                       "(<a href='mailto:mikelima@cirulla.net'>mikelima@cirulla.net</a>)</p>" +
                       "<p>Licensed under the GNU Public License v2 or above</p>" +
                       "<p/><p>Station geolocation data from " +
                       "<a href='http://www.openstreetmap.org'>OpenStreetMap</a></p>" +
                       "<p>Realtime train data from " +
                       "<a href='http://mobile.viaggiatreno.it'>Viaggiatreno</a></p>") +
                  "</div>"
            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
}
