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

QList<QString> RepoAsset::assetLabelInstalledList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::assetLabelRequiredList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::criticalityList = QList<QString>()
        << "High"
        << "Low"
        << "Medium";

QList<QString> RepoAsset::luLCS1List = QList<QString>()
        << "B071 - Paddington Station"
        << "C101 - Liverpool Street Station"
        << "C125 - Bond Street Station"
        << "C175 - Ealing Broadway Station"
        << "CR021 - Reading Station"
        << "CR022 - Reading to Twyford"
        << "CR023 - Twyford Station"
        << "CR024 - Twyford to Maidenhead"
        << "CR031 - Maidenhead Station"
        << "CR032 - Maidenhead to Taplow"
        << "CR033 - Taplow Station"
        << "CR034 - Taplow to Burnham"
        << "CR035 - Burnham Station"
        << "CR036 - Burnham to Slough"
        << "CR037 - Slough Station"
        << "CR038 - Slough to Langley"
        << "CR039 - Langley Station"
        << "CR042 - Langley to Iver"
        << "CR043 - Iver Station"
        << "CR044 - Iver to West Drayton"
        << "CR045 - West Drayton Station"
        << "CR046 - West Drayton to Hayes and Harlington"
        << "CR052 - Heathrow Terminal 5 to Heathrow Central"
        << "CR054 - Heathrow Terminal 4 to Heathrow Central"
        << "CR056 - Heathrow Central to Hayes and Harlington Station"
        << "CR061 - Hayes and Harlington Station"
        << "CR062 - Hayes and Harlington to Southall"
        << "CR063 - Southall Station"
        << "CR064 - Southall to Hanwell"
        << "CR065 - Hanwell Station"
        << "CR066 - Hanwell to West Ealing"
        << "CR067 - West Ealing Station"
        << "CR068 - West Ealing to Ealing Broadway"
        << "CR072 - Ealing Broadway to Acton Main Line"
        << "CR073 - Acton Main Line Station"
        << "CR074 - Acton Main Line to Kensal Town"
        << "CR075 - Kensal Town Station"
        << "CR076 - Kensall Town to Paddington Section"
        << "CR081 - Paddington Station (Crossrail)"
        << "CR082 - Paddington to Bond Street Section"
        << "CR084 - Bond Street to TCR Section"
        << "CR086 - TCR to Farringdon Section"
        << "CR088 - Farringdon to Liverpool Street"
        << "CR092 - Liverpool Street to Whitechapel"
        << "CR094 - Stepney Green Shaft to Stratford Station"
        << "CR094 - Whitechapel Station to Stepney Green Shaft"
        << "CR102 - Stratford to Maryland"
        << "CR103 - Maryland Station"
        << "CR104 - Maryland to Forest Gate"
        << "CR105 - Forest Gate Station"
        << "CR106 - Forest Gate to Manor Park"
        << "CR107 - Manor Park Station"
        << "CR108 - Manor Park to Ilford"
        << "CR109 - Ilford Station"
        << "CR112 - Ilford to Seven Kings"
        << "CR113 - Seven Kings Station"
        << "CR114 - Seven Kings to Goodmayes"
        << "CR115 - Goodmayes Station"
        << "CR116 - Goodmayes to Chadwell Heath"
        << "CR117 - Chadwell Heath Station"
        << "CR118 - Chadwell Heath to Romford"
        << "CR119 - Romford Station"
        << "CR122 - Romford to Gidea Park"
        << "CR123 - Gidea Park Station"
        << "CR124 - Gidea Park to Harold Wood"
        << "CR125 - Harold Wood Station"
        << "CR126 - Harold Wood to Brentwood"
        << "CR127 - Brentwood Station"
        << "CR128 - Brentwood to Shenfield"
        << "CR129 - Shenfield Station"
        << "CR142 - Stepney Green Shaft to Canary Wharf Station"
        << "CR143 - Canary Wharf Station"
        << "CR144 - Canary Wharf Station to Custom House Station"
        << "CR145 - Custom House Station"
        << "CR146 - Connaught Tunnel"
        << "CR146 - Custom House Station to Woolwich Station"
        << "CR147 - Woolwich Station"
        << "CR148 - Woolwich Station to Abbey Wood Station"
        << "CR149 - Abbey Wood Station"
        << "CR501 - Royal Oak Portal"
        << "CR502 - Pudding Mill Lane Portal"
        << "CR503 - Victoria Dock Portal"
        << "CR504 - North Woolwich Portal"
        << "CR505 - Plumstead Portal"
        << "CR511 - Fisher Street Shaft"
        << "CR512 - Stepney Green Shaft"
        << "CR513 - Mile End Park Shaft"
        << "CR514 - Eleanor Street Shaft"
        << "CR515 - Limmo Peninsular Shaft"
        << "CR516 - Plumstead Shaft"
        << "CR521 - Route Control Centre"
        << "CR522 - Kensall Green Bulk Supply"
        << "CR523 - Old Oak Common Depot"
        << "CR524 - Pudding Mill Lane Bulk Supply"
        << "CR525 - Westbourne Park Turnback Facility"
        << "CR526 - Plumsted Depot & Sidings"
        << "CR527 - Ilford Depot Back Up Control Facility"
        << "D061 - Whitechapel Station"
        << "D233 - Heathrow Central"
        << "D235 - Heathrow Terminal 4"
        << "D237 - Heathrow Terminal 5"
        << "M123 - Farringdon Station"
        << "M135 - Moorgate Station"
        << "Mobile Asset"
        << "N105 - Tottenham Court Road Station"
        << "X999 - DEMO Bond Street Station";

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

void RepoAsset::setName(const QString &name)
{
    insert("Name", name);
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

QString RepoAsset::assetLabelInstalled() const
{
    return stringValue("Asset Label Installed");
}

int RepoAsset::assetLabelInstalledIndex() const
{
    return assetLabelInstalledList.indexOf(assetLabelInstalled());
}

QString RepoAsset::assetLabelRequired() const
{
    return stringValue("Asset Label Required");
}

int RepoAsset::assetLabelRequiredIndex() const
{
    return assetLabelRequiredList.indexOf(assetLabelRequired());
}

QString RepoAsset::assetStatus() const
{
    return stringValue("Asset Status");
}

int RepoAsset::assetStatusIndex() const
{
    return operationalStatusList.indexOf(assetStatus());
}

int RepoAsset::assetTagLabelsQuantity() const
{
    return value("Asset Tag Labels Quantity (#)", 0).toInt();
}

QString RepoAsset::criticality() const
{
    return stringValue("Criticality");
}

int RepoAsset::criticalityIndex() const
{
    return criticalityList.indexOf(criticality());
}

QDate RepoAsset::dateOfCommissioning() const
{
    return value("Date of Commissioning").toDate();
}

QString RepoAsset::designAlternativeAssetID() const
{
    return stringValue("Design Alternative Asset ID");
}

int RepoAsset::economicLifeYears() const
{
    return value("Economic Life (Years)", 0).toInt();
}

QDate RepoAsset::expectedLifeExpiryDate() const
{
    return value("Expected Life Expriry Date").toDate();
}

QString RepoAsset::luLCS1() const
{
    return stringValue("LU LCS1");
}

int RepoAsset::luLCS1Index() const
{
    return luLCS1List.indexOf(luLCS1());
}
