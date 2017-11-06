/** o
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

#include "repo_teamspace.h"

using namespace repo;

RepoTeamspace::RepoTeamspace(QObject *parent)
    : QAbstractListModel(parent)
{}

RepoTeamspace::~RepoTeamspace()
{
    clear();
}

void RepoTeamspace::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    int i = 0;
    for (RepoTeamspaceProjectModel* project : modelData)
    {
        delete project;
        modelData[i++] = NULL;
    }
    modelData.clear();
    endRemoveRows();
}

void RepoTeamspace::parseAPI(const QJsonDocument &accountInfo)
{
    clear();

    for (QJsonValue accVal : accountInfo.object()["accounts"].toArray())
    {
        QJsonObject account = accVal.toObject();
        QString accountName = account["account"].toString();

        for (QJsonValue projVal : account["projects"].toArray())
        {
            QJsonObject project = projVal.toObject();
            QString projectName = project["name"].toString();

            for (QJsonValue modelVal : project["models"].toArray())
            {
                QJsonObject model = modelVal.toObject();
                QString modelName = model["name"].toString();
                QUuid uuid = model["model"].toVariant().toUuid();
                bool isFederation = model["federate"].toBool();

                emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
                modelData.append(new RepoTeamspaceProjectModel(accountName, projectName, modelName, uuid, isFederation));
                emit endInsertRows();
            }
        }
    }
}

QVariant RepoTeamspace::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (rowCount() > index.row())
    {
        switch(role)
        {
        case RepoTeamspaceProjectModel::AccountRole :
            ret = modelData[index.row()]->property("account");
            break;
        case RepoTeamspaceProjectModel::ProjectRole :
            ret = modelData[index.row()]->property("project");
            break;
        case RepoTeamspaceProjectModel::ModelRole:
            ret = modelData[index.row()]->property("model");
            break;
        case RepoTeamspaceProjectModel::UuidRole:
            ret = modelData[index.row()]->property("uuid");
            break;
        case RepoTeamspaceProjectModel::FederationRole:
            ret = modelData[index.row()]->property("isFederation");
            break;
        }
    }
    return ret;
}

int RepoTeamspace::rowCount(const QModelIndex &) const
{
    return modelData.size();
}

QHash<int, QByteArray> RepoTeamspace::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RepoTeamspaceProjectModel::AccountRole] = "accountName";
    roles[RepoTeamspaceProjectModel::ProjectRole] = "projectName";
    roles[RepoTeamspaceProjectModel::ModelRole] = "modelName";
    roles[RepoTeamspaceProjectModel::UuidRole] = "uuid";
    roles[RepoTeamspaceProjectModel::FederationRole] = "isFederation";
    return roles;
}
