import QtQuick 1.0
import com.nokia.meego 1.0
import "uiconstants.js" as UiConstants

Rectangle {
    width: parent.width
    height: screen.currentOrientation == Screen.Landscape ?
                UiConstants.HeaderDefaultHeightLandscape :
                UiConstants.HeaderDefaultHeightPortrait
    color: "#071"
}
