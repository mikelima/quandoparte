import QtQuick 1.0

Rectangle {
    id: shadow
    width: parent.width
    height: 5
    z: 10

    gradient: Gradient {
        GradientStop {color: "#99000000"; position: 0.0}
        GradientStop {color: "#00000000"; position: 1.0}
    }
}
