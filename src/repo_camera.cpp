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


#include "repo_camera.h"

// TODO: http://stackoverflow.com/questions/28041741/qt-qml-camera-to-c-qimage-on-android/33238150#33238150
// https://kunalmaemo.blogspot.co.uk/2013/06/using-qml-camera-and-passing-image-to-c.html
repo::RepoCamera::RepoCamera(QObject *parent) : QObject(parent)
{
    std::cout << "RepoCamera initialized" << std::endl;
}

void repo::RepoCamera::retrieveImage(const QString &path)
{

    //    QCamera *camera = qvariant_cast<QCamera *>(path->property("mediaObject"));
    //    QCameraImageCapture *imageCapture = new QCameraImageCapture(camera);

    //    camera->setCaptureMode(QCamera::CaptureStillImage);
    //    camera->start(); // Viewfinder frames start flowing
    //    //on half pressed shutter button
    //    camera->searchAndLock();
    //    //on shutter button pressed
    //    imageCapture->capture();
    //    //on shutter button released
    //    camera->unlock();


    QUrl imageUrl(path);
    QQmlEngine* engine = QQmlEngine::contextForObject(this)->engine();
    QQmlImageProviderBase* imageProviderBase = engine->imageProvider(imageUrl.host());
    QQuickImageProvider* imageProvider = static_cast<QQuickImageProvider*>(imageProviderBase);

    QSize imageSize;
    QString imageId = imageUrl.path().remove(0,1);
    QImage image = imageProvider->requestImage(imageId, &imageSize, imageSize);

    if( !image.isNull())
    {
        processImage(image);
    }




//    QQmlEngine* engine = QQmlEngine::contextForObject(this)->engine();
//    QObject *qmlCamera = engine->findChild<QObject*>("qmlRepoCamera");
//    camera = qvariant_cast<QCamera*>(_qmlCamera->property("mediaObject"));

//    QObject::connect(&videoProbe,
//                     SIGNAL(videoFrameProbed(QVideoFrame)),
//                     this,SLOT(handleFrame(const QVideoFrame&)));
//    videoProbe.setSource(camera);
}

void repo::RepoCamera::processImage(const QImage &image)
{
    std::cout << "processImage" << std::endl;

//    image.save("frame.png");
    //    QImage img = dmtxEncode("hello world!");
    //    img.save("test.png");

//    QString message = RepoDataMatrix::decode(image);
//    std::cout << "Message is: " << message.toStdString() << std::endl;

}


void repo::RepoCamera::handleFrame(const QVideoFrame &frame)
{
    //http://stackoverflow.com/questions/28041741/qt-qml-camera-to-c-qimage-on-android
    std::cout << "handleFrame" << std::endl;
}

