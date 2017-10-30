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

namespace repo {

class RepoNetworkAccessManager : public QNetworkAccessManager
{

    Q_OBJECT

    Q_PROPERTY(QString lastErrorMessage READ getLastErrorMessage WRITE setLastErrorMessage NOTIFY lastErrorMessageChanged MEMBER _lastErrorMessage)

    Q_PROPERTY(QJsonDocument accountInfo READ getAccountInfo WRITE setAccountInfo NOTIFY accountInfoChanged MEMBER _accountInfo)

    enum API {
        LOGIN,
        LIST_INFO
    };

signals:

    void lastErrorMessageChanged(const QString&);

    void accountInfoChanged(const QJsonDocument&);

    void isError();

public:

    RepoNetworkAccessManager(QObject *parent = nullptr);

public slots:

    Q_INVOKABLE void reset();

    Q_INVOKABLE void authenticate(const QString& username, const QString &password);
    void finishedSlot(QNetworkReply*);

    Q_INVOKABLE void getUserInfo(const QString& username);

    Q_INVOKABLE void replyErrored(QNetworkReply::NetworkError);

    Q_INVOKABLE void replySslErrored(QList<QSslError>);

    void replyReady();

    Q_INVOKABLE void setLastErrorMessage(const QString &msg);

    Q_INVOKABLE QString getLastErrorMessage() const;

    Q_INVOKABLE void setAccountInfo(const QJsonDocument &accountInfo);

    Q_INVOKABLE QJsonDocument getAccountInfo() const;

    void processErrorNetworkReply(QNetworkReply* reply);

    QUrl getURL(API api, const QString &param = QString());

    QNetworkRequest getNetworkRequest(const QUrl &url);

    static int getStatusCode(const QNetworkReply *reply);

private :

    QString _lastErrorMessage;

    // API return
    QJsonDocument _accountInfo;

    QString targetServer;

    QString username;

    static const QString DEV_SERVER;

    static const QString PROD_SERVER;

};
}
