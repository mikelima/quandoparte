import QtQuick 1.0
import com.nokia.meego 1.0
import "uiconstants.js" as UiConstants

BorderImage {
    id: root
    property alias text: searchField.text
    width: parent.width
    border {
        left: 10
        right: 10
        top: 10
        bottom: 10
    }
    height: 0
    source: style.background
    states: [
        State {
            name: "visible"
            when: root.visible
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
            duration: 200
            easing.type: Easing.OutBounce
            target: root
            properties: "height"
        }
    }

    ToolBarStyle {
        id: style
    }
    TextField {
        id: searchField
        anchors {
            fill: parent
            leftMargin: UiConstants.DefaultMargin
            rightMargin: UiConstants.DefaultMargin
            topMargin: UiConstants.DefaultMargin
            bottomMargin: UiConstants.DefaultMargin
        }
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
