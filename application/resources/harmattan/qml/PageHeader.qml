import QtQuick 1.0
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import "uiconstants.js" as UiConstants

Rectangle {
    property alias text: label.text
    property alias options: dialog.model
    property alias selectedIndex: dialog.selectedIndex

    id: root
    width: parent.width
    height: screen.currentOrientation == Screen.Landscape ?
                UiConstants.HeaderDefaultHeightLandscape :
    UiConstants.HeaderDefaultHeightPortrait
    color: mouse.pressed ? "#060" : "#071"

    TumblerButtonStyle {
        id: style
        inverted: true
    }
    Item {
        id: spacer
        anchors.left: parent.left
        width: UiConstants.DefaultMargins
        height: parent.heigth
    }
    Label {
        id: label
        anchors.left: spacer.right
        anchors.verticalCenter: parent.verticalCenter
        font {
            pixelSize: UiConstants.HeaderFontPixelSize
            bold: false
        }
        color: style.textColor
    }
    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: dialog.open()
    }

    Image {
        id: icon

        anchors { right: (label.text != "") ? parent.right : undefined;
            rightMargin: UiConstants.DefaultMargins;
            horizontalCenter: (label.text != "") ? undefined : parent.horizontalCenter;
            verticalCenter: parent.verticalCenter;
        }
        height: label.height
        source: "image://theme/meegotouch-combobox-indicator" +
                (style.inverted ? "-inverted" : "") +
                (root.enabled ? "" : "-disabled") +
                (mouse.pressed ? "-pressed" : "")
    }
    SelectionDialog {
        id: dialog
        titleText: qsTr("Show")
    }
}
