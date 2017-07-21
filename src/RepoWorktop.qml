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

    function filterTagCode(tagCode) {
        assetListView.filterTagCode(tagCode)
    }



    RepoAssetGroupListView {
        id: assetGroupListView
        anchors.left: parent.left
        width: parent.width * 0.225
        height: parent.height
        Layout.fillHeight: true
        focus: true

        onCurrentIndexChanged: {
            assetListView.filterGroup(assetGroupListView.currentItem.text)
        }
    }

    Rectangle {
        id: assetListViewRectangle
        anchors.left: assetGroupListView.right
        width: parent.width * 0.3875
        height: parent.height
        color: "white"
        Layout.fillHeight: true
        focus: true

        RepoAssetListView {
            id: assetListView
            anchors.fill: parent
            highlightFollowsCurrentItem: true
            highlightMoveDuration: 200

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

        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0

        delegate:  RepoAssetViewDelegate {
            id: repoAssetViewDelegate
            height: parent.height
            width: assetListViewRectangle.width
//            highlighted: false
        }

        //        onMovingChanged: {
        //            ((RepoAssetViewDelegate) delegate).assignCurrentIndex()
        //            console.log("moving: " + currentIndex)
        //            assetListView.currentIndex = currentIndex
        //        }

        onCurrentIndexChanged: {
            assetListView.currentIndex = currentIndex
        }
    }


}
