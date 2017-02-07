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
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import repo 1.0
import QtGraphicalEffects 1.0


ItemDelegate {



    Flickable {
        width: parent.width
        height: parent.height
        contentHeight: 1000



        Image {
            id: dataMatrixImage
            source: dataMatrix
            width: 250
            height: width
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: tagCodeText
            text: tagCode
            anchors.top: dataMatrixImage.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 20
            topPadding: 8
        }

        Grid {
            id: grid
            columns: 1
            anchors.top: tagCodeText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            width: parent.width - 40

            Label { text: "Tag Code" }
            TextField { text: tagCode; leftPadding: 20; width: parent.width; readOnly: true; }

            Label { text: "Name"; topPadding: 20 }
            TextArea { text: name; leftPadding: 20; wrapMode: TextEdit.Wrap; width: parent.width }

            Label { text: "Description"; topPadding: 20 }
            TextArea { text: description; leftPadding: 20; wrapMode: TextEdit.Wrap; width: parent.width }

            Label { text: "Operational Status"; topPadding: 20}
            ComboBox {
                id: operationalStatusComboBox
                width: parent.width
                model: operationalStatusList
                currentIndex: operationalStatusIndex
                leftPadding: 20
            }

            Label { text: "Asset Label Installed"; topPadding: 20 }
            CheckBox { checked: assetLabelInstalled; }

            Label { text: "Asset Label Required"; topPadding: 20 }
            CheckBox { checked: assetLabelRequired; }


            Label { text: "Asset Status"; topPadding: 20}
            ComboBox {
                id: assetStatusComboBox
                width: parent.width
                model: assetStatusList
                currentIndex: assetStatusIndex
                leftPadding: 20
            }

        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }

    onClicked: {
        assetView.currentIndex = index
    }

}

