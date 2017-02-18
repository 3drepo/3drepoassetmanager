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

#include <QMap>
#include <QVariant>
#include <QString>
#include <QList>
#include <QDate>

namespace repo
{

class RepoAsset : public QMap<QString, QVariant>
{

public :

    //! Returns a string value given a suitable key, empty string if not found.
    QString stringValue(const QString &key) const;

public :

    QString tagCode() const;

    void setTagCode(const QString &tagCode);

    QString name() const;

    void setName(const QString &name);

    QString description() const;

    void setDescription(const QString &description);

    QString operationalStatus() const;

    int operationalStatusIndex() const;

    QString assetLabelInstalled() const;

    int assetLabelInstalledIndex() const;

    QString assetLabelRequired() const;

    int assetLabelRequiredIndex() const;

    QString assetStatus() const;

    int assetStatusIndex() const;

    int assetTagLabelsQuantity() const;

    QString criticality() const;

    int criticalityIndex() const;

    QDate dateOfCommissioning() const;

    QString designAlternativeAssetID() const;

    int economicLifeYears() const;

    QDate expectedLifeExpiryDate() const;

    QString guardrailPrincipleMaterial() const;

    int guardrailPrincipleMaterialIndex() const;

    double heightMetres() const;

    QString kickplatesIncluded() const;

    int kickplatesIncludedIndex() const;

    QString labelTextLineFour() const;

    QString labelTextLineThree() const;

    QString labelTextLineTwo() const;

    double lengthMetres() const;

    double londonSurveyGridX() const;

    double londonSurveyGridY() const;

    double londonSurveyGridZ() const;

    QString luLCS1() const;

    int luLCS1Index() const;

    QString memo() const;

    double meterageMetres() const;

    QString normalTrafficPrimaryDirection() const;

    int normalTrafficPrimaryDirectionIndex() const;

    double safeWorkingLoadKilograms() const;

    QString vehicleProtection() const;

    int vehicleProtectionIndex() const;

    QString fireRating() const;

    int fireRatingIndex() const;

    QString acousticTreatment() const;

    int acousticTreatmentIndex() const;

    QString birdMesh() const;

    int birdMeshIndex() const;

    double depthMillimetres() const;

    double freeAreaPercentage() const;

    double heightMillimetres() const;

    QString insectMesh() const;

    int insectMeshIndex() const;

    double widthMillimetres() const;

    double maximumSlopeAngleDegrees() const;

    QString purposeOfLadder() const;

    int purposeOfLadderIndex() const;

    QString integratedLanding() const;

    int integratedLandingIndex() const;

    QString multiFlightStair() const;

    int multiFlightStairIndex() const;

    int numberOfFlights() const;

    int numberOfFloors() const;

    int numberOfSteps() const;

    QString stairFinish() const;

    int stairFinishIndex() const;

    QString stairMaterial() const;

    int stairMaterialIndex() const;

public :

    static QList<QString> operationalStatusList;

    static QList<QString> assetStatusList;

    static QList<QString> assetLabelInstalledList;

    static QList<QString> assetLabelRequiredList;

    static QList<QString> criticalityList;

    static QList<QString> guardrailPrincipalMaterialList;

    static QList<QString> kickplatesIncludedList;

    static QList<QString> luLCS1List;

    static QList<QString> normalTrafficPrimaryDirectionList;

    static QList<QString> vehicleProtectionList;

    static QList<QString> fireRatingList;

    static QList<QString> acousticTreatmentList;

    static QList<QString> birdMeshList;

    static QList<QString> insectMeshList;

    static QList<QString> purposeOfLadderList;

    static QList<QString> integratedLandingList;

    static QList<QString> multiFlightStairList;

    static QList<QString> stairFinishList;

    static QList<QString> stairMaterialList;
};

}
