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
import repo 1.0

ListView {
    id: assetGroupListView
    focus: true
    currentIndex: -1

    //    model: RepoAssetCategoriesModel {
    //        id: categoriesModel
    //    }

    model: repoTeamspace




    header: Rectangle {
        width: parent.width
        height: crossrailLogo.height + 80
        Layout.fillHeight: true
        color: "white"
        z: 2

        Image {
            id: crossrailLogo
            source: "image://byteimage/" + networkAccessManager.avatar //"qrc:/images/crossrail_logo.svg"
            sourceSize.width: parent.width - 160
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
            antialiasing: true
        }

        Label {
            id: nameField
            leftPadding: 20
            topPadding: 20
            anchors.top: crossrailLogo.bottom
            text: "Paco Lluna"
        }

        Label {
            leftPadding: 20
            topPadding: 5
            anchors.top: nameField.bottom
            color:  "#666"
            text: "paco.lluna@balfourbeatty.com"
        }

        Rectangle {
            implicitHeight: 1
            color: "#ddd"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
    headerPositioning: ListView.InlineHeader  // ListView.PullBackHeader


    delegate:
        ItemDelegate {
        width: parent.width
        text: "  " +  modelName // display
        highlighted: ListView.isCurrentItem
        onClicked: {
            assetView.currentIndex = 0 // reset what the assetView shows
            assetGroupListView.currentIndex = index
        }
    }







    section.property: "accountName"
    section.criteria: ViewSection.FullString
    section.delegate:  ItemDelegate {
        text: section
        font.bold: true
        width: parent.width
    }


    ScrollIndicator.vertical: ScrollIndicator { }
}

