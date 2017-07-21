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

#include <QGuiApplication>
#include <QQmlApplicationEngine>

//obsolete - to be deleted
#include "repo_camera.h"

#include "repo_data_matrix_filter.h"
#include "repo_asset_categories_model.h"
#include "repo_data_matrix_image_provider.h"
#include "repo_asset_filterable_model.h"

int main(int argc, char *argv[])
{
    // http://doc.qt.io/qt-5/qtqml-cppintegration-definetypes.html#registering-an-instantiable-object-type
    qmlRegisterType<repo::RepoCamera>("repo", 1, 0, "RepoCamera");
    qmlRegisterType<repo::RepoDataMatrixFilter>("repo", 1, 0, "RepoDataMatrixFilter");
    qmlRegisterType<repo::RepoAssetCategoriesModel>("repo", 1, 0, "RepoAssetCategoriesModel");
    qmlRegisterType<repo::RepoAssetFilterableModel>("repo", 1, 0, "RepoAssetFilterableModel");

    QGuiApplication::setApplicationName("Crossrail Asset Manager by 3D Repo");
    QGuiApplication::setOrganizationName("3D Repo");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/src/main.qml")));
    engine.addImageProvider(QLatin1String("dataMatrix"), new repo::RepoDataMatrixImageProvider);

    return app.exec();
}
