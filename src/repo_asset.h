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

namespace repo
{

class RepoAsset : public QObject, public QMap<QString, QVariant>
{
    Q_OBJECT

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

    QString description() const;

    QString operationalStatus() const;

    int operationalStatusIndex() const;

    /**
     * Returns true if the associated string field is "Yes", false otherwise.
     * @brief isAssetLabelInstalled
     * @return
     */
    bool assetLabelInstalled() const;

    bool assetLabelRequired() const;

    QString assetStatus() const;

    int assetStatusIndex() const;


public :

    static QList<QString> operationalStatusList;

    static QList<QString> assetStatusList;

};

}
