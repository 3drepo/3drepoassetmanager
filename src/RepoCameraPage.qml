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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import QtMultimedia 5.8
import repo 1.0

Pane {
    id: page

    RepoCamera { // instantiates RepoCamera Object
        id: repoCamera
    }

    Item {
//        width: parent.width
//        height: parent.height
        anchors.fill: parent

        Camera {
            id: camera
            objectName: "qmlRepoCamera"

            imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

            exposure {
                exposureCompensation: -1.0
                exposureMode: Camera.ExposurePortrait
            }

            flash.mode: Camera.FlashRedEyeReduction

            imageCapture {
                onImageCaptured: {
//                    photoPreview.source = preview  // Show the preview in an Image
                    repoCamera.retrieveImage(preview);
                }
            }
        }

        MouseArea{
                anchors.fill: parent
                onClicked: {
                    camera.imageCapture.capture();
                }
            }

        VideoOutput {
            source: camera
            anchors.fill: parent
            focus : visible // to receive focus and capture key events when visible
        }

//        Image {
//            id: photoPreview
//        }
    }
}
