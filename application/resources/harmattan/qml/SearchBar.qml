import QtQuick 1.0
import com.nokia.meego 1.0
import "uiconstants.js" as UiConstants


BorderImage {
    property alias text: searchField.text
    width: parent.width
    border.left: 10
    border.right: 10
    border.top: 10
    border.bottom: 10
    height:  visible ? UiConstants.SearchBarDefaultHeight : 0
    source: style.background

    ToolBarStyle {
        id: style
    }
    Item {
        id: spacerTop
        width: parent.width
        height: UiConstants.DefaultMargin
    }
    Item {
        id: spacerLeft
        anchors.left: parent.left
        width: UiConstants.DefaultMargin
        height: searchField.height
    }
    Item {
        id: spacerRight
        anchors.right: parent.right
        width: UiConstants.DefaultMargin
        height: searchField.height
    }

    TextField {
        id: searchField
        anchors.top: spacerTop.bottom
        anchors.left: spacerLeft.right
        anchors.right: spacerRight.left
        placeholderText: qsTr("Search")
        inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
        platformStyle: TextFieldStyle { paddingRight: clearButton.width }
        onTextChanged: {
            if (searchField.text.length === 0) {
                searchButton.visible = true
                clearButton.visible = false
            } else {
                searchButton.visible = false
                clearButton.visible = true
            }
        }
        Image {
            id: searchButton
            visible: true
            smooth: true
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-common-search"
        }
        Image {
            id: clearButton
            visible: false
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-input-clear"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    inputContext.reset()
                    searchField.text = ""
                }
            }
        }
    }
    Item {
        id: spacerBottom
        width: parent.width
        anchors.top: searchField.bottom
        height: UiConstants.DefaultMargins
    }
}
