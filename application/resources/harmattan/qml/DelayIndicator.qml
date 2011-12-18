import QtQuick 1.0
import "uiconstants.js" as UiConstants

Item {
    id: indicator
    property int level: 0
    width: UiConstants.DefaultMargin
    anchors{
        top: parent.top
        bottom: parent.bottom
    }
    Rectangle {
        id: rect
        width: 10
        height: parent.height
        anchors.left: parent.left
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
