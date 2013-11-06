import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
	anchors.fill: parent
	PageHeader {
	    id: header
	    anchors.top: parent.top
        title: qsTr("About Quando Parte")
	}
	Label {
	    anchors {
		top: header.bottom;
		left: parent.left;
		right: parent.right;
		margins: Theme.paddingLarge
	    }
            fontSizeMode: Text.Fit
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            linkColor: Theme.highlightColor
        text: qsTr("<h2><a href='http://quandoparte.garage.maemo.org'>" +
		       "Quando Parte" + "</a></h2>" +"<p style='font-size:small;'>version ") +
		  settings.versionString +
                  "<div style='font-size:small;'>" +
		  qsTr("</p>" +
                       "<p>Copyright (c) 2010, 2011, 2012, 2013</p>" +
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
