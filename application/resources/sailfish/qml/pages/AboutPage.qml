/*
    Copyright (C) 2011, 2013, 2014 Luciano Montanaro <mikelima@cirulla.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/
import QtQuick 2.1
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        anchors.fill: parent
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
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
                source: "/usr/share/icons/hicolor/86x86/apps/quandoparte.png"
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
        Column {
            anchors.top: firstSection.bottom
            anchors.topMargin: Theme.paddingLarge
            width: parent.width
            spacing: Theme.paddingLarge
            Label {
                width: parent.width
                wrapMode: Text.WordWrap
                linkColor: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Virtual Arrivals and Departures board for Italian trains.")
            }
            Label {
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
}
