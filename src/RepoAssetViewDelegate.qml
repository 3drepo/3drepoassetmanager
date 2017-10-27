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


Item {

    Flickable {
        width: parent.width
        height: parent.height
        contentHeight: grid.height + dataMatrixImage.height + tagCodeText.height + 40

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

//        TableView {
//            TableViewColumn {
//                role: "title"
//                title: "Title"
//                width: 100
//            }
//            TableViewColumn {
//                role: "author"
//                title: "Author"
//                width: 200
//            }
//            model: model
//        }



        Grid {
            id: grid
            columns: 1
            anchors.top: tagCodeText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            width: parent.width - 40

            Label {
                text: qsTr("Tag Code")
                font.bold: true
            }
            TextField {
                text: tagCode
                leftPadding: 20
                width: parent.width
                readOnly: true
            }

            Label { // Mandatory field
                text: qsTr("Name")
                font.bold: true
                topPadding: 20
            }
            TextArea { // max 255 chars
                text: name;
                leftPadding: 20;
                wrapMode: TextEdit.Wrap;
                width: parent.width

                onTextChanged: {
                    if (text != name) // prevents infinite looping
                        assetView.model.setData(index, text, "name")
                }
            }

            Label { text: qsTr("Description"); topPadding: 20 }
            TextArea { // max 2000 chars
                text: description;
                leftPadding: 20;
                wrapMode: TextEdit.Wrap;
                width: parent.width
                onTextChanged: {
                    if (text != description)
                        assetView.model.setData(index, text, "description")
                }
            }

            Label { // Mandatory field
                text: qsTr("Operational Status")
                font.bold: true
                topPadding: 20
            }
            ComboBox {
                id: operationalStatusComboBox
                width: parent.width
                model: operationalStatusList
                currentIndex: operationalStatusIndex
                leftPadding: 20
            }

            Label { text: qsTr("Asset Label Installed"); topPadding: 20}
            ComboBox {
                width: parent.width
                model: assetLabelInstalledList
                currentIndex: assetLabelInstalledIndex
                leftPadding: 20
            }

            Label { text: qsTr("Asset Label Required"); topPadding: 20}
            ComboBox {
                width: parent.width
                model: assetLabelRequiredList
                currentIndex: assetLabelRequiredIndex
                leftPadding: 20
            }

            Label { text: qsTr("Asset Status"); topPadding: 20}
            ComboBox {
                id: assetStatusComboBox
                width: parent.width
                model: assetStatusList
                currentIndex: assetStatusIndex
                leftPadding: 20
            }

            Label { text: qsTr("Asset Tag Labels Quantity (#)"); topPadding: 20}
            SpinBox {
                value: assetTagLabelsQuantity
                leftPadding: 20
                editable: true
                from: 0
                to: 10000
            }

            Label { text: qsTr("Criticality"); topPadding: 20}
            ComboBox {
                width: parent.width
                model: criticalityList
                currentIndex: criticalityIndex
                leftPadding: 20
            }

            Label { text: qsTr("Date of Commissioning"); topPadding: 20; bottomPadding: 5}
            Calendar {
                weekNumbersVisible: false
                frameVisible: true
                //                selectedDate: dateOfCommissioning ? dateOfCommissioning : new Date()
            }

            Label { text: qsTr("Design Alternative Asset ID"); topPadding: 20 }
            TextField {
                text: designAlternativeAssetID;
                leftPadding: 20;
                width: parent.width;
            }

            Label { text: qsTr("Economic Life (Years)"); topPadding: 20}
            SpinBox {
                value: economicLifeYears
                leftPadding: 20
                editable: true
                from: 0
                to: 100
            }

            Label { text: qsTr("Expected Life Expiry Date"); topPadding: 20; bottomPadding: 5}
            Calendar {
                weekNumbersVisible: false
                frameVisible: true
                //                selectedDate: expectedLifeExpiryDate ? expectedLifeExpiryDate : new Date()
            }


            Label {
                text: qsTr("LU LCS1")
                topPadding: 20
                font.bold: true
            }
            ComboBox {
                width: parent.width
                model: luLCS1List
                currentIndex: luLCS1Index
                leftPadding: 20
            }

        }



        ScrollIndicator.vertical: ScrollIndicator { }
    }

//    onClicked: {
//        assetView.currentIndex = index
//    }

}

