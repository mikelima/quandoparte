import QtQuick 1.0
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import "uiconstants.js" as UiConstants
import "PageHeader.js" as Private

Rectangle {
    id: header
    property alias text: label.text
    property alias selectedIndex: dialog.selectedIndex
    property variant options: [
        "Unnamed"
    ]

    width: parent.width
    height: screen.currentOrientation === Screen.Landscape ?
                UiConstants.HeaderDefaultHeightLandscape :
                UiConstants.HeaderDefaultHeightPortrait
    gradient: Gradient {
        GradientStop { color: Qt.darker(UiConstants.AccentColor, mouse.pressed ? 1.5 : 1.25); position: 0.0 }
        GradientStop { color: Qt.lighter(UiConstants.AccentColor, 1.5); position: 1.0 }
    }

    TumblerButtonStyle {
        id: style
        inverted: true
    }
    Label {
        id: label
        anchors {
            left: parent.left;
            leftMargin: UiConstants.DefaultMargin;
            verticalCenter: parent.verticalCenter;
        }
        font {
            pixelSize: UiConstants.HeaderFontPixelSize
            bold: false
        }
        color: style.textColor
    }
    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: if (optionList.count > 1) dialog.open()
    }

    Image {
        id: icon
        anchors {
            right: (label.text != "") ? parent.right : undefined;
            rightMargin: UiConstants.DefaultMargin;
            horizontalCenter: (label.text != "") ? undefined : parent.horizontalCenter;
            verticalCenter: parent.verticalCenter;
        }
        visible: optionList.count > 1
        height: label.height
        source: "image://theme/meegotouch-combobox-indicator" +
                (style.inverted ? "-inverted" : "") +
                (header.enabled ? "" : "-disabled") +
                (mouse.pressed ? "-pressed" : "")
    }
    SelectionDialog {
        id: dialog
        titleText: qsTr("Show")
        model: ListModel {
            id: optionList
        }
    }
    onSelectedIndexChanged: Private.setDisplayIndex(selectedIndex)
    Component.onCompleted: Private.init()
}
