#include "repo_asset_item.h"

using namespace repo;

RepoAssetItem::RepoAssetItem()
{}

QVariant RepoAssetItem::data(int role) const
{
    QVariant data;
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
    case AssetLabelInstalledListRole:
        data = QVariant(asset.assetLabelInstalledList);
        break;
    case AssetLabelInstalledIndexRole:
        data = asset.assetLabelInstalledIndex();
        break;
    case AssetLabelRequiredRole :
        data = asset.assetLabelRequired();
        break;        
    case AssetLabelRequiredListRole:
        data = QVariant(asset.assetLabelRequiredList);
        break;
    case AssetLabelRequiredIndexRole:
        data = asset.assetLabelRequiredIndex();
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
    case AssetTagLabelsQuantityRole:
        data = asset.assetTagLabelsQuantity();
        break;
    case CriticalityRole :
        data = asset.criticality();
        break;
    case CriticalityIndexRole :
        data = asset.criticalityIndex();
        break;
    case CriticalityListRole :
        data = QVariant(asset.criticalityList);
        break;
    case DateOfCommissioningRole:
        data = asset.dateOfCommissioning();
        break;
    case DesignAlternativeAssetIDRole :
        data = asset.designAlternativeAssetID();
        break;
    case EconomicLifeYearsRole:
        data = asset.economicLifeYears();
        break;
    case ExpectedLifeExpiryDateRole:
        data = asset.expectedLifeExpiryDate();
        break;
    case LuLCS1Role:
        data = asset.luLCS1();
        break;
    case LuLCS1IndexRole:
        data = asset.luLCS1Index();
        break;
    case LuLCS1ListRole:
        data = QVariant(asset.luLCS1List);
        break;
    }
    return data;
}

void RepoAssetItem::setData(const QVariant &value, int role)
{
//    switch (role)
//    {
//    case NameRole :
        asset.setName(value.toString());
        std::cout << "setting: " << value.toString().toStdString() << std::endl;
//        break;
//    }
}

void RepoAssetItem::setGroup(const QString &group)
{
    this->group = group;
}

QString RepoAssetItem::getGroup() const
{
    return group;
}

void RepoAssetItem::setAsset(const RepoAsset &asset)
{
    this->asset = asset;
}

RepoAsset RepoAssetItem::getAsset() const
{
    return asset;
}
