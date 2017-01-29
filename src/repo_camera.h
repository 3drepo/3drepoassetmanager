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

#pragma once

#include <QObject>
#include <QCamera>
#include <QVideoProbe>
#include <QCameraImageCapture>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickImageProvider>
#include <QQmlContext>

#include <iostream>

#include "repo_data_matrix.h"

namespace repo
{

// https://blog.qt.io/blog/2015/03/20/introducing-video-filters-in-qt-multimedia/
class RepoCamera : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* qmlCamera READ qmlCamera WRITE setQmlCamera)

public:

    explicit RepoCamera(QObject* parent = 0);

    QObject *qmlCamera() const { return _qmlCamera; }

    void setQmlCamera(QObject *qmlCamera) { _qmlCamera = qmlCamera; }

public slots:

    void retrieveImage(const QString &path);

    void processImage(const QImage &image);

    void handleFrame(const QVideoFrame &frame);

private :
    QCamera *camera;
    QVideoProbe videoProbe;

    QObject * _qmlCamera;
};
}
