import QtQuick 1.0
import com.nokia.meego 1.0

Item {
    property alias text: searchField.text
    width: parent.width
    height: 48

    TextField {
        id: searchField
        width: parent.width
        anchors.margins: 16
        anchors.centerIn: parent
        placeholderText: qsTr("Search")
        inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
        platformStyle: TextFieldStyle { paddingRight: clearButton.width }
        onTextChanged: {
            if (searchField.text.length == 0) {
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
