import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: indicator
    property int level: 0
    width: 10
    height: parent.height
    anchors {
        top: parent.top
        bottom: parent.bottom
        rightMargin: Theme.paddingMedium
    }
    Rectangle {
        id: rect
        width: 10
        height: indicator.height - 10
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
