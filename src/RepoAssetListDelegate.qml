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
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import repo 1.0
import QtGraphicalEffects 1.0

ItemDelegate {
    id: delegateItem
    width: parent.width
    height: 120

    Image {
        id: dataMatrixImage
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height - 20
        width: height
        anchors.left: parent.left
        source: dataMatrix
        anchors.leftMargin: 10
    }

    Text {
        id: tagCodeText
        text: /*tagCode*/ display
        anchors.left: dataMatrixImage.right
        font.pixelSize: 20
        width: delegateItem.width - dataMatrixImage.width - 10
        elide: Text.ElideRight
        topPadding: 24
        leftPadding: 10
    }

    Text {
        id: nameText
        text: name
        anchors.left: dataMatrixImage.right
        anchors.top: tagCodeText.bottom
        font.pixelSize: 14
        color: "#999"
        width: tagCodeText.width
        elide: Text.ElideRight
        topPadding: 8
        leftPadding: tagCodeText.leftPadding
    }

    Text {
        text: description
        anchors.left: dataMatrixImage.right
        anchors.top: nameText.bottom
        font.pixelSize: nameText.font.pixelSize
        color: nameText.color
        width: tagCodeText.width
        elide: Text.ElideRight
        topPadding: 4
        leftPadding: tagCodeText.leftPadding
    }

    Rectangle {
        implicitHeight: 1
        color: "#ddd"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}

