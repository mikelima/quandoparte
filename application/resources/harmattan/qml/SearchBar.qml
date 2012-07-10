import QtQuick 1.0
import com.nokia.meego 1.0
import "uiconstants.js" as UiConstants

Image {
    id: root
    property alias text: searchField.text
    property bool open: false

    fillMode: Image.Tile
    height: 0
    width: parent.width
    clip: true
    ToolBarStyle {
        id: style
    }
    BorderImage {
        id: border
        anchors {
            bottom: root.bottom
        }
        width: root.width
        height: UiConstants.SearchBarDefaultHeight
        border {
            left: 10
            right: 10
            top: 10
            bottom: 10
        }
        source: style.background
        TextField {
            id: searchField
            anchors {
                fill: parent
                leftMargin: UiConstants.DefaultMargin
                topMargin: UiConstants.DefaultMargin
                rightMargin: UiConstants.DefaultMargin
                bottomMargin: UiConstants.DefaultMargin
            }
            height: implicitHeight
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
    }
    states: [
        State {
            name: "open"
            when: root.open
            changes: [
                PropertyChanges {
                    target: root
                    height: UiConstants.SearchBarDefaultHeight
                }
            ]
        }
    ]
    transitions: Transition {
        PropertyAnimation {
            duration: style.visibilityTransitionDuration
            easing.type: Easing.OutBounce
            target: root
            properties: "height"
        }
    }
}
