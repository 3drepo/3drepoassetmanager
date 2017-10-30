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

namespace repo {

class RepoTeamspaceProjectModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString account READ account WRITE setAccount NOTIFY accountChanged)
    Q_PROPERTY(QString project READ project WRITE setProject NOTIFY projectChanged)
    Q_PROPERTY(QString model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid NOTIFY uuidChanged)
    Q_PROPERTY(bool isFederation READ isFederation WRITE setIsFederation NOTIFY isFederationChanged)

public :

    enum ProjectRoles {
        AccountRole = Qt::UserRole + 1,
        ProjectRole,
        ModelRole,
        UuidRole,
        FederationRole
    };

    RepoTeamspaceProjectModel(const QString &account,
                          const QString &project,
                          const QString &model,
                          const QUuid &uuid,
                          const bool isFederation = false);

signals :

    void accountChanged(const QString&);
    void projectChanged(const QString&);
    void modelChanged(const QString&);
    void uuidChanged(const QUuid &);
    void isFederationChanged(bool);

public slots :

    Q_INVOKABLE void setAccount(const QString &account);
    Q_INVOKABLE QString account() const;

    Q_INVOKABLE void setProject(const QString &project);
    Q_INVOKABLE QString project() const;

    Q_INVOKABLE void setModel(const QString &model);
    Q_INVOKABLE QString model() const;

    Q_INVOKABLE void setUuid(const QUuid &uuid);
    Q_INVOKABLE QUuid uuid() const;

    Q_INVOKABLE void setIsFederation(bool on);
    Q_INVOKABLE bool isFederation() const;


private :

    QString _account;
    QString _project;
    QString _model;
    QUuid _uuid;
    bool _isFederation;
};
}
