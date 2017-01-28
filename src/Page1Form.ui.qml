import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias rectangle: rectangle

    RowLayout {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 0
        anchors.top: parent.top

        ItemDelegate {
            id: itemDelegate
            text: qsTr("Item Delegate")
        }

        Rectangle {
            id: rectangle
            x: 125
            width: parent.width/3
            height: parent.height
            color: "#e64747"
        }

        ListView {
            id: listView
            x: 0
            y: 0
            width: 110
            height: parent.height
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    spacing: 10
                }
            }
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }
    }
}
