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

#include <QString>
#include <QStandardItem>

#include <iostream>
#include "repo_asset.h"

namespace repo {

class RepoAssetItem : public QStandardItem
{

public :

    enum AssetRoles {
        GroupRole = Qt::UserRole + 1,
        TagCodeRole,
        NameRole,
        DescriptionRole,
        DataMatrixRole,
        OperationalStatusRole,
        OperationalStatusIndexRole,
        OperationalStatusListRole,
        AssetLabelInstalledRole,
        AssetLabelInstalledListRole,
        AssetLabelInstalledIndexRole,
        AssetLabelRequiredRole,
        AssetLabelRequiredListRole,
        AssetLabelRequiredIndexRole,
        AssetStatusRole,
        AssetStatusIndexRole,
        AssetStatusListRole,
        AssetTagLabelsQuantityRole,
        CriticalityRole,
        CriticalityIndexRole,
        CriticalityListRole,
        DateOfCommissioningRole,
        DesignAlternativeAssetIDRole,
        EconomicLifeYearsRole,
        ExpectedLifeExpiryDateRole,
        LuLCS1Role,
        LuLCS1IndexRole,
        LuLCS1ListRole
    };

public:

    RepoAssetItem();

    QVariant data(int role = Qt::UserRole + 1) const;

    virtual void setData(const QVariant &value, int role = Qt::UserRole + 1);

public :

    void setGroup(const QString &group);

    QString getGroup() const;

    void setAsset(const RepoAsset &asset);

    RepoAsset getAsset() const;

private :

    QString group;

    RepoAsset asset;
};
}
