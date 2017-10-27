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

QHash<int, QByteArray> RepoAssetFilterableModel::roles = {
    {RepoAssetItem::TagCodeRole,  "tagCode"},
    {RepoAssetItem::GroupRole, "group"},
    {RepoAssetItem::NameRole, "name"},
    {RepoAssetItem::DescriptionRole, "description"},
    {RepoAssetItem::DataMatrixRole, "dataMatrix"},
    {RepoAssetItem::OperationalStatusRole, "operationalStatus"},
    {RepoAssetItem::OperationalStatusIndexRole, "operationalStatusIndex"},
    {RepoAssetItem::OperationalStatusListRole, "operationalStatusList"},
    {RepoAssetItem::AssetLabelInstalledRole, "assetLabelInstalled"},
    {RepoAssetItem::AssetLabelInstalledIndexRole, "assetLabelInstalledIndex"},
    {RepoAssetItem::AssetLabelInstalledListRole, "assetLabelInstalledList"},
    {RepoAssetItem::AssetLabelRequiredRole, "assetLabelRequired"},
    {RepoAssetItem::AssetLabelRequiredIndexRole, "assetLabelRequiredIndex"},
    {RepoAssetItem::AssetLabelRequiredListRole, "assetLabelRequiredList"},
    {RepoAssetItem::AssetStatusRole, "assetStatus"},
    {RepoAssetItem::AssetStatusIndexRole, "assetStatusIndex"},
    {RepoAssetItem::AssetStatusListRole, "assetStatusList"},
    {RepoAssetItem::AssetTagLabelsQuantityRole, "assetTagLabelsQuantity"},
    {RepoAssetItem::CriticalityRole, "criticality"},
    {RepoAssetItem::CriticalityIndexRole, "criticalityIndex"},
    {RepoAssetItem::CriticalityListRole, "criticalityList"},
    {RepoAssetItem::DateOfCommissioningRole, "dateOfCommissioning"},
    {RepoAssetItem::DesignAlternativeAssetIDRole, "designAlternativeAssetID"},
    {RepoAssetItem::EconomicLifeYearsRole, "economicLifeYears"},
    {RepoAssetItem::ExpectedLifeExpiryDateRole, "expectedLifeExpiryDate"},
    {RepoAssetItem::LuLCS1Role, "luLCS1"},
    {RepoAssetItem::LuLCS1IndexRole, "luLCS1Index"},
    {RepoAssetItem::LuLCS1ListRole, "luLCS1List"}
};

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
    QString path = "Assets\\";
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFileInfo file(it.next());
        QString baseName = file.baseName();
        if (file.suffix() == "csv"
                && baseName.contains("L")
                && baseName.contains("-"))
        {
            QList<RepoAsset> csvAssets = RepoCSVParser::parseCSV(file.absoluteFilePath());
            for (RepoAsset asset : csvAssets)
            {
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
    setFilterRole(role);
    setFilterFixedString(text);
}

void RepoAssetFilterableModel::filterGroup(const QString &group)
{
//    filter(group, RepoAssetItem::GroupRole);
    groupFilter = group == "All assets" ? "" : group;
    invalidateFilter();
}

void RepoAssetFilterableModel::filterTagCode(const QString &tagCode)
{
//    filter(tagCode, RepoAssetItem::TagCodeRole);
    textFilter = tagCode;
    invalidateFilter();
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

bool RepoAssetFilterableModel::setData(int row, const QVariant &value, const QVariant &roleName)
{
    bool success = false;
    int role = getRole(roleName);
    if (role)
    {
        success = setData(index(row, 0), value, role);
    }
    return success;
}

bool RepoAssetFilterableModel::hasData(int row, const QVariant &roleName)
{
    RepoAssetItem *item = (RepoAssetItem*) model->itemFromIndex(mapToSource(index(row, 0)));
//    item->hasData()
    return false;
}

bool RepoAssetFilterableModel::filterAcceptsRow(
        int sourceRow,
        const QModelIndex &) const
{
    bool accept = false;
    RepoAssetItem *item = (RepoAssetItem*) model->item(sourceRow);
    if (item != NULL)
    {
        QString comparator = textFilter.toLower();
        accept = (item->getGroup() == groupFilter || groupFilter.isEmpty()) &&
                 (item->data(RepoAssetItem::TagCodeRole).toString().toLower().contains(comparator)
                    || (item->data(RepoAssetItem::NameRole).toString().toLower().contains(comparator))
                    || (item->data(RepoAssetItem::DescriptionRole).toString().toLower().contains(comparator)));
    }
    return accept;
}

QHash<int, QByteArray> RepoAssetFilterableModel::roleNames() const
{
    return roles;
}

int RepoAssetFilterableModel::getRole(const QVariant &roleName) const
{
    return roles.key(roleName.toByteArray(), -1);
}
