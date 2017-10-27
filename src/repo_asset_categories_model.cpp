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

#include "repo_asset_categories_model.h"

#include <QDebug>

repo::RepoAssetCategoriesModel::RepoAssetCategoriesModel(QObject *parent)
    : QStringListModel(parent)
{
    populate();
}


void repo::RepoAssetCategoriesModel::populate()
{
    QStringList fileNames;
    fileNames.append("All assets");
    QString path = "Assets";

    qDebug() << QDir::currentPath();


    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFileInfo file(it.next());
        QString baseName = file.baseName();

        if (file.suffix() == "csv" && baseName.contains("L")
                && baseName.contains("-"))
            fileNames.append(baseName);
    }
    this->setStringList(fileNames);

}
