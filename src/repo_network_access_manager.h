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
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QImage>
#include <QPixmap>
#include <QVariant>
#include <QString>
#include <QDataStream>

#include "repo_teamspace.h"
#include "repo_material_icons.h"

namespace repo {

class RepoNetworkAccessManager : public QNetworkAccessManager
{

    Q_OBJECT

    Q_PROPERTY(QString lastErrorMessage NOTIFY lastErrorMessageChanged MEMBER m_lastErrorMessage)

    Q_PROPERTY(QJsonDocument accountInfo NOTIFY accountInfoChanged MEMBER m_accountInfo)
    Q_PROPERTY(QString username NOTIFY usernameChanged MEMBER m_username)
    Q_PROPERTY(QString email NOTIFY emailChanged MEMBER m_email)
    Q_PROPERTY(QString avatarBytes NOTIFY avatarBytesChanged MEMBER m_avatarBytes)

public :

    enum API {
        LOGIN,
        LIST_INFO,
        AVATAR
    };
    Q_ENUM(API)

signals:

    void lastErrorMessageChanged(const QString&);

    void accountInfoChanged(const QJsonDocument&);
    void usernameChanged(const QString&);
    void emailChanged(const QString&);
    void avatarBytesChanged(const QString&);

    void isError();

//    void teamspaceChanged();

public:

    RepoNetworkAccessManager(QObject *parent = nullptr);

public slots:

    Q_INVOKABLE void reset();

    Q_INVOKABLE void authenticate(const QString& username, const QString &password);

    void finishedSlot(QNetworkReply*);

    Q_INVOKABLE void fetchUserInfo(const QString& username);

    Q_INVOKABLE void fetchAvatar(const QString& username);

    Q_INVOKABLE void replyErrored(QNetworkReply::NetworkError);

    Q_INVOKABLE void replySslErrored(QList<QSslError>);

    void processErrorNetworkReply(QNetworkReply* reply);

    QUrl getURL(API api, const QString &param = QString());

    QNetworkRequest getNetworkRequest(const QUrl &url);

    static int getStatusCode(const QNetworkReply *reply);

private :

    QString m_lastErrorMessage;

    // API return
    QList<RepoTeamspaceProjectModel*> modelData;
    QJsonDocument m_accountInfo;
    QString m_username;
    QString m_email;
    QString m_avatarBytes;

private :

    QString targetServer;

    static const QString DEV_SERVER;

    static const QString PROD_SERVER;

};
}
