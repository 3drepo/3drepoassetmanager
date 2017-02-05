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

#include <QAbstractListModel>
#include <QModelIndex>
#include <QPixmap>
#include <QIcon>

#include <iostream>

#include "repo_asset.h"
#include "repo_csv_parser.h"
#include "repo_data_matrix.h"

namespace repo {

class RepoAssetModel : public QAbstractListModel
{

    Q_OBJECT

public:

    enum AssetRoles {
        TagCodeRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        DataMatrixRole
    };

public:

    RepoAssetModel(QObject *parent = Q_NULLPTR);

    Q_INVOKABLE void populate(const QString &filename = QString());

    Q_INVOKABLE QMap<QString, QVariant>  asset(int index) const;

    void clear();

public :

    //! Returns the number of elements in this asset model
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    //! Returns 1
    inline int columnCount(const QModelIndex &) const { return 1; }

    //! Returns data for given index
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const;

private :

    QVariantList assets;
};

}
