import QtQuick 1.1
import "uiconstants.js" as UiConstants

Item {
    id: indicator
    property int level: 0
    width: 10
    height: parent.height
    anchors {
        top: parent.top
        bottom: parent.bottom
        rightMargin: UiConstants.SmallMargin
    }
    Rectangle {
        id: rect
        width: 10
        height: UiConstants.ListItemHeightLarge - 10
        anchors.centerIn: parent
        color: {
            switch (indicator.level) {
            case 0: return "#0b0"
            case 1: return "#dd0"
            case 2: return "#da0"
            case 3: return "#d60"
            case 4: return "#d00"
            default: return "#b0b"
            }
        }
    }
}
