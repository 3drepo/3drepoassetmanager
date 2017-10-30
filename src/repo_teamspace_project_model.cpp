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

#include "repo_teamspace_project_model.h"

using namespace repo;

RepoTeamspaceProjectModel::RepoTeamspaceProjectModel(const QString &account,
                                             const QString &project,
                                             const QString &model,
                                             const QUuid &uuid,
                                             bool isFederation)
{
    setAccount(account);
    setProject(project);
    setModel(model);
    setUuid(uuid);
    setIsFederation(isFederation);
}


void RepoTeamspaceProjectModel::setAccount(const QString &account)
{
    if (_account != account)
    {
        _account = account;
        emit accountChanged(_account);
    }
}

QString RepoTeamspaceProjectModel::account() const
{
    return _account;
}

void RepoTeamspaceProjectModel::setProject(const QString &project)
{
    if (_project != project)
    {
        _project = project;
        emit projectChanged(_project);
    }
}

QString RepoTeamspaceProjectModel::project() const
{
    return _project;
}

void RepoTeamspaceProjectModel::setModel(const QString &model)
{
    if (_model != model)
    {
        _model = model;
        emit modelChanged(_model);
    }
}

QString RepoTeamspaceProjectModel::model() const
{
    return _model;
}

void RepoTeamspaceProjectModel::setUuid(const QUuid &uuid)
{
    if (_uuid != uuid)
    {
        _uuid = uuid;
        emit uuidChanged(_uuid);
    }
}

QUuid RepoTeamspaceProjectModel::uuid() const
{
    return _uuid;
}

void RepoTeamspaceProjectModel::setIsFederation(bool on)
{
    if (_isFederation != on)
    {
        _isFederation = on;
        emit isFederationChanged(_isFederation);
    }
}

bool RepoTeamspaceProjectModel::isFederation() const
{
    return _isFederation;
}


