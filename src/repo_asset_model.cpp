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

#include "repo_asset_model.h"

repo::RepoAssetModel::RepoAssetModel(QObject *parent)
    : QAbstractListModel(parent)
{
    populate();
}

void repo::RepoAssetModel::populate(const QString &filename)
{
    clear();

    if (!filename.isEmpty())
    {
        QString filePath = "c:\\Users\\jozef\\Documents\\3D Models\\BB\\Crossrail\\Exports\\C530-010-UF-004-UPDDAT-01\\" + filename;

        QVariantList csvAssets = RepoCSVParser::parseCSV(filePath);
        emit beginInsertRows(QModelIndex(), 0, csvAssets.size());
        assets = csvAssets;
        emit endInsertRows();
    }
}

QMap<QString, QVariant> repo::RepoAssetModel::asset(int index) const
{
//    RepoAsset asset;
//    if (index < assets.size())
//        asset = assets.at(index);
    return assets.at(index).toMap();
}

void repo::RepoAssetModel::clear()
{
    emit beginRemoveRows(QModelIndex(),0,assets.size());
    assets.clear();
    emit endRemoveRows();
}

int repo::RepoAssetModel::rowCount(const QModelIndex &) const
{
    return assets.size() ;
}


QVariant repo::RepoAssetModel::data(const QModelIndex &index, int role) const
{
    // See http://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html
    QVariant data;

    if (index.row() < assets.size())
    {
        RepoAsset asset(assets.at(index.row()));
        switch (role)
        {
        case TagCodeRole :
            data = asset.tagCode();
            break;
        case NameRole :
            data = asset.name();
            break;
        case DescriptionRole :
            data = asset.description();
            break;
        case DataMatrixRole :
            data = QString("image://dataMatrix/" + asset.tagCode());
            break;
        }
    }
    return data;
}

QHash<int, QByteArray> repo::RepoAssetModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagCodeRole] = "tagCode";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[DataMatrixRole] = "dataMatrix";
    return roles;
}



