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

#include <QObject>
#include <QString>
#include <QUuid>
#include <QVariant>

namespace repo {

class RepoTeamspaceProjectModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString account NOTIFY accountChanged MEMBER m_account)
    Q_PROPERTY(QString project NOTIFY projectChanged MEMBER m_project)
    Q_PROPERTY(QString model NOTIFY modelChanged MEMBER m_model)
    Q_PROPERTY(QUuid uuid NOTIFY uuidChanged MEMBER m_uuid)
    Q_PROPERTY(bool isFederation NOTIFY isFederationChanged MEMBER m_isFederation)

public :

    enum ProjectRoles {
        AccountRole = Qt::UserRole + 1,
        ProjectRole,
        ModelRole,
        UuidRole,
        FederationRole
    };
    Q_ENUM(ProjectRoles)

    RepoTeamspaceProjectModel(const QString &account,
                          const QString &project,
                          const QString &model,
                          const QUuid &uuid,
                          bool isFederation = false);

signals :

    void accountChanged(const QString&);
    void projectChanged(const QString&);
    void modelChanged(const QString&);
    void uuidChanged(const QUuid &);
    void isFederationChanged(bool);

private :

    QString m_account;
    QString m_project;
    QString m_model;
    QUuid m_uuid;
    bool m_isFederation;
};
}
