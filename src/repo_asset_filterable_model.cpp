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

#include "repo_asset_filterable_model.h"

using namespace repo;

RepoAssetFilterableModel::RepoAssetFilterableModel()
    : QSortFilterProxyModel()
{
    setDynamicSortFilter(true);
    //    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSourceModel(&model);

    populate();
}

void RepoAssetFilterableModel::populate()
{
    //    clear();

    QString path = "c:\\Users\\jozef\\Documents\\3D Models\\BB\\Crossrail\\Exports\\";
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFileInfo file(it.next());
        QString baseName = file.baseName();
        if (file.suffix() == "csv" && baseName.contains("L")
                && baseName.contains("-"))
        {
            QVariantList csvAssets = RepoCSVParser::parseCSV(file.absoluteFilePath());
            for (QVariant v : csvAssets)
            {
                RepoAsset asset(v);
                RepoAssetItem *item = new RepoAssetItem();
                item->setText(asset.tagCode());
                item->setSection(baseName);
                model.appendRow(item);
            }
        }
    }
}

QVariant RepoAssetFilterableModel::data(const QModelIndex &index, int role) const
{
    // See http://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html
    QVariant data;

    RepoAssetItem *item = (RepoAssetItem *) model.item(index.row());

    data = item->text();

    //    if (index.row() < assets.size())
    //    {
    //        RepoAsset asset(assets.at(index.row()));
    //        switch (role)
    //        {
    //        case TagCodeRole :
    //            data = asset.tagCode();
    //            break;
    //        case NameRole :
    //            data = asset.name();
    //            break;
    //        case DescriptionRole :
    //            data = asset.description();
    //            break;
    //        case DataMatrixRole :
    //            data = QString("image://dataMatrix/" + asset.tagCode());
    //            break;
    //        case OperationalStatusRole :
    //            data = asset.operationalStatus();
    //            break;
    //        case OperationalStatusIndexRole :
    //            data = asset.operationalStatusIndex();
    //            break;
    //        case OperationalStatusListRole :
    //            data = QVariant(asset.operationalStatusList);
    //            break;
    //        case AssetLabelInstalledRole :
    //            data = asset.assetLabelInstalled();
    //            break;
    //        case AssetLabelRequiredRole :
    //            data = asset.assetLabelRequired();
    //            break;
    //        case AssetStatusRole :
    //            data = asset.assetStatus();
    //            break;
    //        case AssetStatusIndexRole :
    //            data = asset.assetStatusIndex();
    //            break;
    //        case AssetStatusListRole :
    //            data = QVariant(asset.assetStatusList);
    //            break;
    //        }
    //    }
    return data;
}

QHash<int, QByteArray> RepoAssetFilterableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagCodeRole] = "tagCode";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[DataMatrixRole] = "dataMatrix";
    roles[OperationalStatusRole] = "operationalStatus";
    roles[OperationalStatusIndexRole] = "operationalStatusIndex";
    roles[OperationalStatusListRole] = "operationalStatusList";
    roles[AssetLabelInstalledRole] = "assetLabelInstalled";
    roles[AssetLabelRequiredRole] = "assetLabelRequired";
    roles[AssetStatusRole] = "assetStatus";
    roles[AssetStatusIndexRole] = "assetStatusIndex";
    roles[AssetStatusListRole] = "assetStatusList";
    return roles;
}
