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

class RepoCamera : public QObject
{
    Q_OBJECT

public:
    explicit RepoCamera(QObject *parent = 0);

public slots:
    void retrieveImage(const QString &path);

    void processImage(const QImage &image);



    //--------------------------------------------------------------------------


    void handleFrame(QVideoFrame &frame);

private :
    QCamera *camera;
    QVideoProbe videoProbe;

};
}
