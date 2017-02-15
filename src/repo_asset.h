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

    RepoAsset() : QMap<QString, QVariant>() {}

    RepoAsset(const QMap<QString, QVariant> &m) : QMap<QString, QVariant>(m) {}

    RepoAsset(const QVariant &v) : RepoAsset(v.toMap()) {}

public :

    //! Returns a string value given a suitable key, empty string if not found.
    QString stringValue(const QString &key) const;

public :

    QString tagCode() const;

    QString name() const;

    void setName(const QString &name);

    QString description() const;

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

    QString luLCS1() const;

    int luLCS1Index() const;

public :

    static QList<QString> operationalStatusList;

    static QList<QString> assetStatusList;

    static QList<QString> assetLabelInstalledList;

    static QList<QString> assetLabelRequiredList;

    static QList<QString> criticalityList;

    static QList<QString> luLCS1List;

};

}
