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

bool RepoAssetFilterableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool success = false;
    RepoAssetItem *item = (RepoAssetItem*) model->itemFromIndex(mapToSource(index));
    if (success = (item != NULL))
    {
        item->setData(value, role);
        emit dataChanged(index, index, QVector<int>() << role);
    }
    return success;
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
    roles[RepoAssetItem::AssetLabelInstalledIndexRole] = "assetLabelInstalledIndex";
    roles[RepoAssetItem::AssetLabelInstalledListRole] = "assetLabelInstalledList";
    roles[RepoAssetItem::AssetLabelRequiredRole] = "assetLabelRequired";
    roles[RepoAssetItem::AssetLabelRequiredIndexRole] = "assetLabelRequiredIndex";
    roles[RepoAssetItem::AssetLabelRequiredListRole] = "assetLabelRequiredList";
    roles[RepoAssetItem::AssetStatusRole] = "assetStatus";
    roles[RepoAssetItem::AssetStatusIndexRole] = "assetStatusIndex";
    roles[RepoAssetItem::AssetStatusListRole] = "assetStatusList";
    roles[RepoAssetItem::AssetTagLabelsQuantityRole] = "assetTagLabelsQuantity";
    roles[RepoAssetItem::CriticalityRole] = "criticality";
    roles[RepoAssetItem::CriticalityIndexRole] = "criticalityIndex";
    roles[RepoAssetItem::CriticalityListRole] = "criticalityList";
    roles[RepoAssetItem::DateOfCommissioningRole] = "dateOfCommissioning";
    roles[RepoAssetItem::DesignAlternativeAssetIDRole] = "designAlternativeAssetID";
    roles[RepoAssetItem::EconomicLifeYearsRole] = "economicLifeYears";
    roles[RepoAssetItem::ExpectedLifeExpiryDateRole] = "expectedLifeExpiryDate";
    roles[RepoAssetItem::LuLCS1Role] = "luLCS1";
    roles[RepoAssetItem::LuLCS1IndexRole] = "luLCS1Index";
    roles[RepoAssetItem::LuLCS1ListRole] = "luLCS1List";
    return roles;
}
