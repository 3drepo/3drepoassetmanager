/**
*  Copyright (C) 2017 3D Repo Ltd
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Affero General Public License as
*  published by the Free Software Foundation, either version 3 of the
*  License, or (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Affero General Public License for more details.
*
*  You should have received a copy of the GNU Affero General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.1
//import QtQuick.Controls.Material 2.0

import repo 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Crossrail Asset Manager by 3D Repo")

    Shortcut {
        sequence: "Esc"
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            listView.currentIndex = -1
        }
    }

    header: ToolBar {
        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {
                implicitWidth: 84
                implicitHeight: 84
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: stackView.depth > 1 ? "image://materialicons/arrowBack" :  "image://materialicons/menu"
                    sourceSize.width: 32
                    sourceSize.height: 32
                }
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                        listView.currentIndex = -1
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                id: projectLabel
                text: "Crossrail C530"
                font.pixelSize: 20
                elide: Label.ElideRight
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "white"
            }

            Image {
                id: bbLogo
                source: "qrc:/resources/3D-Repo_white.svg"
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                antialiasing: true
                sourceSize.height: 32
            }


            ToolButton {
                id: cameraButton
                implicitWidth: 84
                implicitHeight: 84
                anchors.right: moreVertToolButton.left
                anchors.rightMargin: -24
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image://materialicons/camera"
                    antialiasing: true
//                    sourceSize.width: 32
//                    sourceSize.height: 32
                }
                onClicked: {
                    if (stackView.depth <= 1) {
                    stackView.push("qrc:/src/RepoCameraPage.qml")
                    var camera = stackView.currentItem
                    camera.tagCodeDetected.connect(relay)
                    }
                }
            }

            ToolButton {
                id: moreVertToolButton
                implicitWidth: 84
                implicitHeight: 84
                anchors.right: parent.right
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image://materialicons/moreVert"
                    sourceSize.width: 32
                    sourceSize.height: 32
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Sign in"
                        onTriggered: repoLoginDialog.open()
                    }
                    MenuItem {
                        text: "About"
                        onTriggered: aboutDialog.open()
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: parent.width * 0.225
        height: window.height
        dragMargin: stackView.depth > 1 ? 0 : undefined

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()

                    // This needs fixing as sometimes this would not be RepoCameraPage object
                    var camera = stackView.currentItem
                    camera.tagCodeDetected.connect(relay)
                }
            }

            model: ListModel {
                ListElement { title: "Crossrail C530"; }
                ListElement { title: "Crossrail C512"; }
                ListElement { title: "Camera"; source: "qrc:/src/RepoCameraPage.qml" }
                ListElement { title: "Drawing"; source: "qrc:/src/RepoDrawing.qml" }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Qt.resolvedUrl("RepoWorktop.qml")
    }

    RepoLoginDialog {
        id: repoLoginDialog
    }

    function relay(tagCode) {
        if (tagCode) {
//            stackView.pop()
//            listView.currentIndex = -1
//              stackView.currentItem.filterGroup("All assets")
              stackView.currentItem.filterTagCode(tagCode)
        }
    }
}
