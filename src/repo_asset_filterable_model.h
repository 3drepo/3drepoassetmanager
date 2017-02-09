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

#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QDir>
#include <QDirIterator>

#include "repo_asset.h"
#include "repo_csv_parser.h"
#include "repo_asset_item.h"

namespace repo {

class RepoAssetFilterableModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    RepoAssetFilterableModel();

    ~RepoAssetFilterableModel();

public :

    Q_INVOKABLE void populate();

    Q_INVOKABLE void filter(const QString &text = QString(), int role = Qt::UserRole + 1);

    Q_INVOKABLE void filterGroup(const QString &group);

    Q_INVOKABLE void filterTagCode(const QString &tagCode);

    QHash<int, QByteArray> roleNames() const;

private :

    QStandardItemModel *model; //! Source model

};
}

