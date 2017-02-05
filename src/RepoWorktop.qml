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

    Rectangle {
        id: assetListViewRectangle
        anchors.left: assetGroupListView.right
        width: parent.width * 0.3785
        height: parent.height
        color: "white"
        Layout.fillHeight: true
        focus: true

        RepoAssetListView {
            id: assetListView
            anchors.fill: parent

            onCurrentIndexChanged: {
                assetView.currentIndex = currentIndex
            }
        }
    }

    DropShadow {
        anchors.fill: assetListViewRectangle
        horizontalOffset: 0
        verticalOffset: 0
        radius: 14.0
        samples: 17
        color: "#30000000"
        source: assetListViewRectangle
    }

    RepoAssetView {
        id: assetView
        anchors.left: assetListViewRectangle.right
        anchors.right: parent.right
        height: parent.height
        model: assetListView.model

        delegate: ItemDelegate {
            height: parent.height
            width: assetListViewRectangle.width + 22

            onClicked: {
                assetView.currentIndex = index
            }

            Image {
                id: dataMatrixImage
                source: dataMatrix;
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                text: tagCode;
                anchors.top: dataMatrixImage.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 20
            }
        }

        onCurrentIndexChanged: {
            assetListView.currentIndex = currentIndex
        }
    }
}
