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

QList<QString> RepoAsset::guardrailPrincipalMaterialList = QList<QString>()
        << "Glass"
        << "Steel"
        << "Wood";

QList<QString> RepoAsset::kickplatesIncludedList = QList<QString>()
        << "No"
        << "Yes";

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

QList<QString> RepoAsset::normalTrafficPrimaryDirectionList = QList<QString>()
        << "Cross Over"
        << "E/B"
        << "W/B";

QList<QString> RepoAsset::vehicleProtectionList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::fireRatingList = QList<QString>()
        << "30"
        << "60";

QList<QString> RepoAsset::acousticTreatmentList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::birdMeshList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::insectMeshList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::purposeOfLadderList = QList<QString>()
        << "Access"
        << "Fire Escape"
        << "Inspection";

QList<QString> RepoAsset::integratedLandingList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::multiFlightStairList = QList<QString>()
        << "No"
        << "Yes";

QList<QString> RepoAsset::stairFinishList = QList<QString>()
        << "Asphalt"
        << "Asphalt Infill"
        << "Asphalt Infill; Ciron Nosing"
        <<  "Asphalt Infill; Concrete"
         << "Asphalt Infill; G M Nosing"
         << "Asphalt Infill; Metal Nosing"
         << "Asphalt Infill; Vinyl Treads"
         << "Asphalt Nosing; Asphalt Tread"
         << "Asphalt; G M Nosing"
         << "Brick"
         << "Carpeted"
         << "Carpeted; Painted"
         << "Cast Iron Nosing"
         << "CI"
         << "Ciron Nosing"
         << "Ciron Nosing; Con; Painted"
         << "Ciron Nosing; Con; Streamline"
         << "Ciron Nosing; Concrete"
         << "Ciron Nosing; Concrete; Tiled"
         << "Ciron Nosing; G M Nosing"
         << "Ciron Nosing; Metal"
         << "Ciron Nosing; Painted Infill"
         << "Ciron Nosing; Streamline"
         << "Ciron Nosing; Tiled Infill"
         << "Ciron Nosing; Timber"
         << "Ciron Nosing; Timber; Asphalt"
         << "Ciron Nosing; Vinyl"
         << "Ciron Nosing; Vinyl Infill"
         << "Ciron Nosing; Vinyl; Concrete"
         << "Concrete"
         << "Concrete Infill"
         << "Concrete Infill; G M Nosing"
         << "Concrete Infill; Tiled Infill"
         << "Concrete Infill; Tiled Nosing"
         << "Concrete Insert"
         << "Concrete Nosing; Concrete"
         << "Concrete; G M Nosing"
         << "Concrete; Metal"
         << "Concrete; Metal Treads"
         << "Concrete; Streamline"
         << "Concrete; Tiled Infill Treads"
         << "Escalator"
         << "G M Nosing"
         << "G M Nosing; Painted"
         << "G M Nosing; Painted Infill"
         << "G M Nosing; Streamline"
         << "G M Nosing; Tiled Infill"
         << "G M Nosing; Timber"
         << "G M Nosing; Timber Infill"
         << "G M Nosing; Vinyl Treads"
         << "Gm/Ciron Nose;Tile Infill;Conc"
         << "Grip Fast"
         << "Grip Fast Nosing; Concrete"
         << "Grip Fast Nosing; Tiled"
         << "Grip Fast Treads; Vinyl Infill"
         << "Grip Fast; Vinyl"
         << "Grip Fast; Vinyl Treads"
         << "Gun Metal Nosing"
         << "Laminate"
         << "Metal"
         << "Metal & Asphalt"
         << "Metal Nosing"
         << "Metal Nosing; Concrete Infill"
         << "Metal Nosing; Streamline"
         << "Metal Nosing; Vinyl"
         << "Metal Nosing; Vinyl Infill"
         << "Metal Treads"
         << "Metal Treads; Timber"
         << "Metal; Painted"
         << "Metal; Vinyl"
         << "Metal; Vinyl Treads"
         << "Streamline"
         << "Tiled"
         << "Tiled Infil Treads"
         << "Timber"
         << "Varna/Rubber"
         << "Vinyl Treads";

QList<QString> RepoAsset::stairMaterialList = QList<QString>()
        << "Concrete"
        << "Other"
        << "Steel"
        << "Wood";

QString RepoAsset::stringValue(const QString &key) const
{
     return value(key, QString()).toString();
}

QString RepoAsset::tagCode() const
{
    return stringValue("Tag Code");
}

void RepoAsset::setTagCode(const QString &tagCode)
{
    insert("Tag Code", tagCode);
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

void RepoAsset::setDescription(const QString &description)
{
    insert("Description", description);
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

QString RepoAsset::guardrailPrincipleMaterial() const
{
    return stringValue("Guardrail Principal Material");
}

int RepoAsset::guardrailPrincipleMaterialIndex() const
{
    return guardrailPrincipalMaterialList.indexOf(guardrailPrincipleMaterial());
}

double RepoAsset::heightMetres() const
{
    return value("Height (Metres)", 0).toDouble();
}

QString RepoAsset::kickplatesIncluded() const
{
    return stringValue("Kickplates Included");
}

int RepoAsset::kickplatesIncludedIndex() const
{
    return kickplatesIncludedList.indexOf(kickplatesIncluded());
}

QString RepoAsset::labelTextLineFour() const
{
    return stringValue("Label Text Line Four");
}

QString RepoAsset::labelTextLineThree() const
{
    return stringValue("Label Text Line Three");
}

QString RepoAsset::labelTextLineTwo() const
{
    return stringValue("Label Text Line Two");
}

double RepoAsset::lengthMetres() const
{
    return value("Length (Metres)", 0).toDouble();
}

double RepoAsset::londonSurveyGridX() const
{
    return value("London Survey Grid X", 0).toDouble();
}

double RepoAsset::londonSurveyGridY() const
{
    return value("London Survey Grid Y", 0).toDouble();
}

double RepoAsset::londonSurveyGridZ() const
{
    return value("London Survey Grid Z", 0).toDouble();
}

QString RepoAsset::luLCS1() const
{
    return stringValue("LU LCS1");
}

int RepoAsset::luLCS1Index() const
{
    return luLCS1List.indexOf(luLCS1());
}

QString RepoAsset::memo() const
{
    return stringValue("Memo");
}

double RepoAsset::meterageMetres() const
{
    return value("Meterage (Metres)").toDouble();
}

QString RepoAsset::normalTrafficPrimaryDirection() const
{
    return stringValue("Normal Traffic-Primary Direction");
}

int RepoAsset::normalTrafficPrimaryDirectionIndex() const
{
    return normalTrafficPrimaryDirectionList.indexOf(normalTrafficPrimaryDirection());
}

double RepoAsset::safeWorkingLoadKilograms() const
{
    return value("Safe Working Load (Kilograms)").toDouble();
}

QString RepoAsset::vehicleProtection() const
{
    return stringValue("Vehicle Protection");
}

int RepoAsset::vehicleProtectionIndex() const
{
    return vehicleProtectionList.indexOf(vehicleProtection());
}

QString RepoAsset::fireRating() const
{
    return stringValue("Fire Rating");
}

int RepoAsset::fireRatingIndex() const
{
    return fireRatingList.indexOf(fireRating());
}

QString RepoAsset::acousticTreatment() const
{
    return stringValue("Acoustic Treatment");
}

int RepoAsset::acousticTreatmentIndex() const
{
    return acousticTreatmentList.indexOf(acousticTreatment());
}

QString RepoAsset::birdMesh() const
{
    return stringValue("Bird Mesh");
}

int RepoAsset::birdMeshIndex() const
{
    return birdMeshList.indexOf(birdMesh());
}

double RepoAsset::depthMillimetres() const
{
    return value("Depth (Millimetres)", 0).toDouble();
}

double RepoAsset::freeAreaPercentage() const
{
    return value("Free Area (Percentage)", 0).toDouble();
}

double RepoAsset::heightMillimetres() const
{
    return value("Height (Millimetres)").toDouble();
}

QString RepoAsset::insectMesh() const
{
    return stringValue("Insect Mesh");
}

int RepoAsset::insectMeshIndex() const
{
    return insectMeshList.indexOf(insectMesh());
}

double RepoAsset::widthMillimetres() const
{
    return value("Width (Millimetres)", 0).toDouble();
}

double RepoAsset::maximumSlopeAngleDegrees() const
{
    return value("Maximum Slope Angle (Degrees)").toDouble();
}

QString RepoAsset::purposeOfLadder() const
{
    return stringValue("Purpose of Ladder");
}

int RepoAsset::purposeOfLadderIndex() const
{
    return purposeOfLadderList.indexOf(purposeOfLadder());
}

QString RepoAsset::integratedLanding() const
{
    return stringValue("Integrated Landing");
}

int RepoAsset::integratedLandingIndex() const
{
    return integratedLandingList.indexOf(integratedLanding());
}

QString RepoAsset::multiFlightStair() const
{
    return stringValue("Multi-Flight Stair");
}

int RepoAsset::multiFlightStairIndex() const
{
    return multiFlightStairList.indexOf(multiFlightStair());
}

int RepoAsset::numberOfFlights() const
{
    return value("Number of Flights (#)").toInt();
}

int RepoAsset::numberOfFloors() const
{
    return value("Number of Floors (#)").toInt();
}

int RepoAsset::numberOfSteps() const
{
    return value("Number of Steps (#)").toInt();
}

QString RepoAsset::stairFinish() const
{
    return stringValue("Stair Finish");
}

int RepoAsset::stairFinishIndex() const
{
    return stairFinishList.indexOf(stairFinish());
}

QString RepoAsset::stairMaterial() const
{
    return stringValue("Stair Material");
}

int RepoAsset::stairMaterialIndex() const
{
    return stairMaterialList.indexOf(stairMaterial());
}
