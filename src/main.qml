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

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("3D Repo Asset Guru")

    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/drawer.png"
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
                id: titleLabel
                text: "3D Repo Asset Guru"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/menu.png"
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                        onTriggered: settingsDialog.open()
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
        width: Math.min(window.width, window.height) / 3 * 2
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
                }
            }

            model: ListModel {
                ListElement { title: "BusyIndicator"; source: "qrc:/src/Page1.qml" }
                ListElement { title: "Button"; source: "qrc:/pages/ButtonPage.qml" }
                ListElement { title: "CheckBox"; source: "qrc:/pages/CheckBoxPage.qml" }
                ListElement { title: "ComboBox"; source: "qrc:/pages/ComboBoxPage.qml" }
                ListElement { title: "Dial"; source: "qrc:/pages/DialPage.qml" }
                ListElement { title: "Dialog"; source: "qrc:/pages/DialogPage.qml" }
                ListElement { title: "Delegates"; source: "qrc:/pages/DelegatePage.qml" }
                ListElement { title: "Frame"; source: "qrc:/pages/FramePage.qml" }
                ListElement { title: "GroupBox"; source: "qrc:/pages/GroupBoxPage.qml" }
                ListElement { title: "PageIndicator"; source: "qrc:/pages/PageIndicatorPage.qml" }
                ListElement { title: "ProgressBar"; source: "qrc:/pages/ProgressBarPage.qml" }
                ListElement { title: "RadioButton"; source: "qrc:/pages/RadioButtonPage.qml" }
                ListElement { title: "RangeSlider"; source: "qrc:/pages/RangeSliderPage.qml" }
                ListElement { title: "ScrollBar"; source: "qrc:/pages/ScrollBarPage.qml" }
                ListElement { title: "ScrollIndicator"; source: "qrc:/pages/ScrollIndicatorPage.qml" }
                ListElement { title: "Slider"; source: "qrc:/pages/SliderPage.qml" }
                ListElement { title: "SpinBox"; source: "qrc:/pages/SpinBoxPage.qml" }
                ListElement { title: "StackView"; source: "qrc:/pages/StackViewPage.qml" }
                ListElement { title: "SwipeView"; source: "qrc:/pages/SwipeViewPage.qml" }
                ListElement { title: "Switch"; source: "qrc:/pages/SwitchPage.qml" }
                ListElement { title: "TabBar"; source: "qrc:/pages/TabBarPage.qml" }
                ListElement { title: "TextArea"; source: "qrc:/pages/TextAreaPage.qml" }
                ListElement { title: "TextField"; source: "qrc:/pages/TextFieldPage.qml" }
                ListElement { title: "ToolTip"; source: "qrc:/pages/ToolTipPage.qml" }
                ListElement { title: "Tumbler"; source: "qrc:/pages/TumblerPage.qml" }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Qt.resolvedUrl("Page1.qml")

        /*Pane {
            id: pane
            Label {
                text: "Qt Quick Controls 2 provides a set of controls that can be used to build complete interfaces in Qt Quick."
                anchors.margins: 20
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                wrapMode: Label.Wrap
            }
        }*/
    }

//    SwipeView {
//        id: swipeView
//        anchors.fill: parent
//        currentIndex: tabBar.currentIndex

//        Page1 {
//        }

//        Page {
//            Label {
//                text: qsTr("Second page")
//                anchors.centerIn: parent
//            }
//        }
//    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex
//        TabButton {
//            text: qsTr("First")
//        }
//        TabButton {
//            text: qsTr("Second")
//        }
//    }
}
