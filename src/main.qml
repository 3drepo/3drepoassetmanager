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
import QtQuick.Controls.Material 2.1
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1
//import QtQuick.Controls.Material 2.0

import repo 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Crossrail Asset Manager by 3D Repo")

    Component.onCompleted: {
        repoLoginDialog.open()
//        repoTeamspaces.populate()
    }


    Shortcut {
        sequence: "Esc"
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
        }
    }

    header: ToolBar {
        Material.foreground: "white"
        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {
                id: menuButton
                anchors.left: parent.left
                anchors.leftMargin: 4
                implicitWidth: 84
                implicitHeight: 84
                onClicked:  {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    } else {
                        drawer.open()
                    }
                }

                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: stackView.depth > 1 ? "image://materialicons/arrowBack" :  "image://materialicons/menu"
                    sourceSize.width: 32
                    sourceSize.height: 32
                }
            }

            Image {
                id: repoLogo
                anchors.left: menuButton.right
                anchors.leftMargin: 12
                source: "qrc:/resources/3D-Repo_white.svg"
                fillMode: Image.PreserveAspectFit
                antialiasing: true
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
                    source: "image://materialicons/accountCircle"
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


    RepoDrawer {
        id: drawer
    }

    RepoTeamspace {
        id: repoTeamspace
    }

    RepoLoginDialog {
        id: repoLoginDialog
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Qt.resolvedUrl("RepoWorktop.qml")
    }

    RepoNetworkAccessManager {
        id: networkAccessManager
        onFinished: {
        }

        onIsError: {
            repoLoginDialog.visible = true // This is a known bug in Qt,
                                       // it should not close the dialog but it does
        }
        onAccountInfoChanged: {
            repoTeamspace.parseAPI(accountInfo)
        }
    }

    function relay(tagCode) {
        if (tagCode) {
            //            stackView.pop()
            //            menuListView.currentIndex = -1
            //              stackView.currentItem.filterGroup("All assets")
            stackView.currentItem.filterTagCode(tagCode)
        }
    }
}
