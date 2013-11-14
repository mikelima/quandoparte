import QtQuick 1.1
import com.nokia.meego 1.1
import "uiconstants.js" as UiConstants

Page {
    anchors.fill: parent

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon {
            iconId: "icon-m-toolbar-back" + (theme.inverted ? "-white": "")
            onClicked: pageStack.pop()
        }
    }
    PageHeader {
        id: header
        anchors.top: parent.top
        selectedIndex: settings.showArrivalsPreferred ? 1 : 0
        options: [
            qsTr("About Quando Parte")
        ]
    }
    DroppedShadow {
        id: shadow
        anchors.top: header.bottom
    }
    Flickable {
        anchors {
            top: header.bottom;
            left: parent.left;
            right: parent.right;
            margins: UiConstants.DefaultMargin
        }
        Row {
            anchors.top: parent.top
            id: firstSection
            spacing: UiConstants.DefaultMargin
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "/usr/share/icons/hicolor/meegotouch/apps/quandoparte.png"
            }
            Label {
                textFormat: Text.RichText
                text: "<style>a:link{color:" + UiConstants.AccentColor + ";text-decoration:none}</style>" +
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
                topMargin: UiConstants.DefaultMargin
            }
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            text: "<style>a:link{color:" + UiConstants.AccentColor + ";text-decoration:none}</style>" +
                  "<div style='font-size:small'>" +
                  qsTr("<p>Copyright (c) 2010, 2011, 2012, 2013</p>" +
                       "<p>Luciano Montanaro " +
                       "(<a href='mailto:mikelima@cirulla.net'>mikelima@cirulla.net</a>)</p>" +
                       "<p>Licensed under the GNU Public License v2 or above</p>" +
                       "<p>Station geolocation data from " +
                       "<a href='http://www.openstreetmap.org'>OpenStreetMap</a></p>" +
                       "<p>Realtime train data from " +
                       "<a href='http://mobile.viaggiatreno.it'>Viaggiatreno</a></p>") +
                  "</div>"
            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
 }
