import QtQuick 1.1
import com.nokia.meego 1.0
import "uiconstants.js" as UiConstants

Page {
    anchors.fill: parent

    tools: ToolBarLayout {
        id: toolBar
        ToolIcon { iconId: "icon-m-toolbar-back"; onClicked: pageStack.pop(); }
    }
    PageHeader {
        id: header
        anchors.top: parent.top
        selectedIndex: settings.showArrivalsPreferred ? 1 : 0
        options: ListModel {
            id: dialogOptions
            ListElement {
                name: QT_TR_NOOP("About Quando Parte")
            }
        }
    }
    Label {
        anchors {
            top: header.bottom;
            left: parent.left;
            right: parent.right;
            margins: UiConstants.DefaultMargins
        }
        text: qsTr("<h2><a href='http://quandoparte.garage.maemo.org'>" +
                   "Quando Parte" + "</a></h2>" +"<p style='font-size:small;'>version " + "0.4.80" +
                   "</p>" +
                   "<p>Copyright (c) 2010, 2011</p>" +
                   "<p>Luciano Montanaro (<a href='mailto:mikelima@cirulla.net'>mikelima@cirulla.net</a>)</p>" +
                   "<p>Licensed under the GNU Public License v2 or above</p>" +
                   "<p/><p>Station geolocation data from " +
                   "<a href='http://www.openstreetmap.org'>OpenStreetMap</a></p>" +
                   "<p>Realtime train data from " +
                   "<a href='http://mobile.viaggiatreno.it'>Viaggiatreno</a></p>");
        onLinkActivated: Qt.openUrlExternally(link)
    }
    LabelStyle {
        id: labelStyle
    }
 }
