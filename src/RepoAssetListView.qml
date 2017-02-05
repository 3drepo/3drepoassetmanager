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
import QtGraphicalEffects 1.0

ListView {
    id: assetListView
    focus: true
    currentIndex: -1
    snapMode: ListView.SnapToItem

    model: RepoAssetModel {
        id: assetModel
    }

    delegate: RepoAssetListDelegate {
        highlighted: ListView.isCurrentItem
        onClicked: {
            assetListView.currentIndex = index
        }
    }

    ScrollIndicator.vertical: ScrollIndicator {}

    function select(selectedItem) {
        assetModel.populate(selectedItem);
    }
}
