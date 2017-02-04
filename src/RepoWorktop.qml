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
import QtGraphicalEffects 1.0

import repo 1.0

Pane {
    padding: 0

    RepoAssetGroupListView {
        id: assetGroupListView
        anchors.left: parent.left
        width: parent.width * 0.225
        height: parent.height
        Layout.fillHeight: true
        focus: true

        onCurrentIndexChanged: {
            assetListView.select(assetGroupListView.currentItem.text)
        }

    }

//    Rectangle {
//        id: rectangle
//        anchors.left: parent.left
//        width: parent.width * 0.25
//        height: parent.height
//        color: "#e64747"
//        Layout.fillHeight: true
//    }


    Rectangle {
        id: rectangle
        anchors.left: assetGroupListView.right
        width: parent.width * 0.378
        height: parent.height
//        color: "white"
        Layout.fillHeight: true
        focus: true

        RepoAssetListView {
            id: assetListView
            anchors.fill: parent
        }
    }

    DropShadow {
        anchors.fill: rectangle
        horizontalOffset: 0
        verticalOffset: 0
        radius: 14.0
        samples: 17
        color: "#30000000"
        source: rectangle
    }

//    ListView {
//        id: listView2
//        focus: true
//        currentIndex: -1
//        anchors.fill: parent

//        delegate:


//            ItemDelegate {
//                width: parent.width


//                text: model.title + "\t" + count

//                highlighted: ListView.isCurrentItem

//                onClicked: {
//                    listView.currentIndex = index
//                    stackView.push(model.source)

//            }
//        }

//        model: ListModel {
//            ListElement { title: "L21253 - Guardrails"; count: 39; }

//        }

//        ScrollIndicator.vertical: ScrollIndicator { }
//    }

}
