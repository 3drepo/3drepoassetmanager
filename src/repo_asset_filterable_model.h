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

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Q_INVOKABLE bool setData(int row, const QVariant &value, const QVariant &roleName);

    Q_INVOKABLE bool hasData(int row, const QVariant &roleName);

    //! See http://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html
    QHash<int, QByteArray> roleNames() const;

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private :

    /**
     * Returns an asset role given a string representation of it, -1 if none
     * found. Beware that this lookup is inefficient as it requires linear
     * looping through the roles hash map.
     *
     * @brief getRole
     * @param roleName
     * @return
     */
    int getRole(const QVariant &roleName) const;

private :

    QStandardItemModel *model; //! Source model

    //! Roles associated with items in the model
    static QHash<int, QByteArray> roles;

    QString groupFilter;

    QString textFilter;

};
}

