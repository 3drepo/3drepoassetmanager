#include "repo_asset_item.h"

using namespace repo;

RepoAssetItem::RepoAssetItem()
{}

QVariant RepoAssetItem::data(int role) const
{
    QVariant data;
    RepoAsset asset(getAsset());
    switch (role)
    {
    case GroupRole :
        data = getGroup();
        break;
    case TagCodeRole :
        data = asset.tagCode();
        break;
    case NameRole :
        data = asset.name();
        break;
    case DescriptionRole :
        data = asset.description();
        break;
    case DataMatrixRole :
        data = QString("image://dataMatrix/" + asset.tagCode());
        break;
    case OperationalStatusRole :
        data = asset.operationalStatus();
        break;
    case OperationalStatusIndexRole :
        data = asset.operationalStatusIndex();
        break;
    case OperationalStatusListRole :
        data = QVariant(asset.operationalStatusList);
        break;
    case AssetLabelInstalledRole :
        data = asset.assetLabelInstalled();
        break;
    case AssetLabelRequiredRole :
        data = asset.assetLabelRequired();
        break;
    case AssetStatusRole :
        data = asset.assetStatus();
        break;
    case AssetStatusIndexRole :
        data = asset.assetStatusIndex();
        break;
    case AssetStatusListRole :
        data = QVariant(asset.assetStatusList);
        break;
    }
    return data;
}

void RepoAssetItem::setGroup(const QString &group)
{
    this->group = group;
}

QString RepoAssetItem::getGroup() const
{
    return group;
}

void RepoAssetItem::setAsset(const QMap<QString, QVariant> &assetInfo)
{
    this->assetInfo = assetInfo;
}

QMap<QString, QVariant> RepoAssetItem::getAsset() const
{
    return assetInfo;
}
