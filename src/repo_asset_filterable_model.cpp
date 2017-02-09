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
    , model(new QStandardItemModel())
{
    setDynamicSortFilter(true);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSourceModel(model);
    populate();
}

RepoAssetFilterableModel::~RepoAssetFilterableModel()
{
    delete model;
}

void RepoAssetFilterableModel::populate()
{
    emit beginInsertRows(QModelIndex(), 0, 0);
    QString path = "c:\\Users\\jozef\\Documents\\3D Models\\BB\\Crossrail\\Exports\\";
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFileInfo file(it.next());
        QString baseName = file.baseName();
        if (file.suffix() == "csv"
                && baseName.contains("L")
                && baseName.contains("-"))
        {
            QVariantList csvAssets = RepoCSVParser::parseCSV(file.absoluteFilePath());
            for (QVariant v : csvAssets)
            {
                RepoAsset asset(v);
                RepoAssetItem *item = new RepoAssetItem();
                item->setText(asset.tagCode());
                item->setGroup(baseName);
                item->setAsset(asset);
                model->appendRow(item);
            }
        }
    }
    emit endInsertRows();
}

void RepoAssetFilterableModel::filter(const QString &text, int role)
{
    invalidateFilter();
    setFilterFixedString(text);
    setFilterRole(role);
}

void RepoAssetFilterableModel::filterGroup(const QString &group)
{
    filter(group, RepoAssetItem::GroupRole);
}

void RepoAssetFilterableModel::filterTagCode(const QString &tagCode)
{
    filter(tagCode, RepoAssetItem::TagCodeRole);
}

QHash<int, QByteArray> RepoAssetFilterableModel::roleNames() const
{
    // See http://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html
    QHash<int, QByteArray> roles;
    roles[RepoAssetItem::TagCodeRole] = "tagCode";
    roles[RepoAssetItem::GroupRole] = "group";
    roles[RepoAssetItem::NameRole] = "name";
    roles[RepoAssetItem::DescriptionRole] = "description";
    roles[RepoAssetItem::DataMatrixRole] = "dataMatrix";
    roles[RepoAssetItem::OperationalStatusRole] = "operationalStatus";
    roles[RepoAssetItem::OperationalStatusIndexRole] = "operationalStatusIndex";
    roles[RepoAssetItem::OperationalStatusListRole] = "operationalStatusList";
    roles[RepoAssetItem::AssetLabelInstalledRole] = "assetLabelInstalled";
    roles[RepoAssetItem::AssetLabelRequiredRole] = "assetLabelRequired";
    roles[RepoAssetItem::AssetStatusRole] = "assetStatus";
    roles[RepoAssetItem::AssetStatusIndexRole] = "assetStatusIndex";
    roles[RepoAssetItem::AssetStatusListRole] = "assetStatusList";
    return roles;
}
