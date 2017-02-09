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

import QtQuick 2.6
import QtQuick.Controls 2.1
import QtMultimedia 5.8
import QtQuick.Dialogs 1.2

import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0

import repo 1.0

Pane {
    id: cameraPage
    padding: 0

    signal tagCodeDetected(string message)

    Rectangle {
        color: "black"
        anchors.fill: parent

        RepoDataMatrixFilter {
            id: dataMatrixFilter            
            onFinished: {
                var scaleX = parent.width / result.resolution.width
                var scaleY = parent.height / result.resolution.height
//                var offsetX = (cameraOutput.width - result.resolution.width)/2

                detectorRectangle.x = result.rectangle.x * scaleX
                detectorRectangle.y = result.rectangle.y * scaleY

                detectorRectangle.width = result.rectangle.width * scaleX
                detectorRectangle.height = result.rectangle.height * scaleY

                detectedText.text = result.message
                detectedText.font.pixelSize = 0.1 * detectorRectangle.height

                tagCodeDetected(result.message)
            }
        }



        VideoOutput {
            id: cameraOutput
            source: camera
            anchors.fill: parent
            filters: [ dataMatrixFilter ]
            focus : visible // to receive focus and capture key events when visible
        }

        Item {
            anchors.fill: parent

            Camera { // http://doc.qt.io/qt-5/qml-qtmultimedia-camera.html
                id: camera
                objectName: "qmlRepoCamera"

                imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

                exposure {
                    exposureCompensation: -1.0
                    exposureMode: Camera.ExposurePortrait
                }

                flash.mode: Camera.FlashRedEyeReduction

//                imageCapture {
//                    onImageCaptured: {
//                        //                    photoPreview.source = preview  // Show the preview in an Image
////                        repoCamera.retrieveImage(preview);
//                    }
//                }
            }

            Rectangle {
                id: detectorRectangle
                color: "transparent"
                border.color: "red"
                border.width: 5
            }

            Text {
                id: detectedText
                anchors.top: detectorRectangle.bottom
                anchors.horizontalCenter: detectorRectangle.horizontalCenter
                text: "Data Matrix"
                color: "red"
            }


            //        MouseArea{
            //                anchors.fill: parent
            //                onClicked: {
            //                    camera.imageCapture.capture();
            //                }
            //            }



            //        Image {
            //            id: photoPreview
            //        }
        }
    }
}
