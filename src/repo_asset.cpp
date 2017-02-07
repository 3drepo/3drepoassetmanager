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

#include "repo_asset.h"

using namespace repo;

QList<QString> RepoAsset::operationalStatusList = QList<QString>()
        << "Abandoned in Place"
        << "Installed"
        << "Planned"
        << "Uninstalled";

QList<QString> RepoAsset::assetStatusList = QList<QString>()
        << "Commissioned"
        << "Construction"
        << "Decommissioned In-situ"
        << "Decommissioned Removed"
        << "Design"
        << "Operational"
        << "Strategic Spare"
        << "Temporary"
        << "Test & Commissioning";

QString RepoAsset::stringValue(const QString &key) const
{
     return value(key, QString()).toString();
}

QString RepoAsset::tagCode() const
{
    return stringValue("Tag Code");
}

QString RepoAsset::name() const
{
    return stringValue("Name");
}

QString RepoAsset::description() const
{
    return stringValue("Description");
}

QString RepoAsset::operationalStatus() const
{
    return stringValue("Operational Status");
}

int RepoAsset::operationalStatusIndex() const
{
    return operationalStatusList.indexOf(operationalStatus());
}

bool RepoAsset::assetLabelInstalled() const
{
    return (stringValue("Asset Label Installed") == "Yes");
}

bool RepoAsset::assetLabelRequired() const
{
    return (stringValue("Asset Label Required") == "Yes");
}

QString RepoAsset::assetStatus() const
{
    return stringValue("Asset Status");
}

int RepoAsset::assetStatusIndex() const
{
    return operationalStatusList.indexOf(assetStatus());
}
