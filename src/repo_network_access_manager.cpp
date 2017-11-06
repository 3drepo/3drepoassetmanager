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

#include "repo_network_access_manager.h"

using namespace repo;


const QString RepoNetworkAccessManager::DEV_SERVER = "dev";

const QString RepoNetworkAccessManager::PROD_SERVER = "post.www";

RepoNetworkAccessManager::RepoNetworkAccessManager(QObject *parent)
    : QNetworkAccessManager(parent)
    , targetServer(PROD_SERVER)
{
    connect(this, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));
}

void RepoNetworkAccessManager::reset()
{
    setProperty("lastErrorMessage", QString());
}


void RepoNetworkAccessManager::authenticate(
        const QString& username,
        const QString &password)
{
    reset();

    setProperty("username", username);

    QUrlQuery postData;
    postData.addQueryItem("username", username);
    postData.addQueryItem("password", password);


    QNetworkReply *reply = this->post(getNetworkRequest(getURL(LOGIN)),
                                      postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyErrored(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(replySslErrored(QList<QSslError>)));
}

void RepoNetworkAccessManager::finishedSlot(QNetworkReply* reply)
{
    QUrl url = reply->url();

    QString username = property("username").toString();

    if (getStatusCode(reply) != 200)
    {
        processErrorNetworkReply(reply);
    }
    else
    {
        if (url == getURL(LOGIN))
        {
            QVariant v = reply->header(QNetworkRequest::SetCookieHeader);
            QList<QNetworkCookie> c = qvariant_cast<QList<QNetworkCookie>>(v);
            this->cookieJar()->setCookiesFromUrl(c, reply->url());

            fetchUserInfo(username);
        }
        else if (url == getURL(LIST_INFO, username))
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(((QString) reply->readAll()).toUtf8());
            setProperty("email", jsonDoc.object()["email"].toString());

            if (jsonDoc.object()["hasAvatar"].toBool())
                fetchAvatar(username);

            setProperty("accountInfo", jsonDoc);
        }
        else if (url == getURL(AVATAR, username))
        {
            setProperty("avatarBytes", reply->readAll().toHex());
        }
    }
    reply->deleteLater();
}

int RepoNetworkAccessManager::getStatusCode(const QNetworkReply *reply)
{
    int statusCode = 0;
    if (reply)
        statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode;
}


void RepoNetworkAccessManager::fetchUserInfo(const QString& username)
{
    reset();
    QNetworkReply *reply = this->get(getNetworkRequest(getURL(LIST_INFO, username)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyErrored(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(replySslErrored(QList<QSslError>)));
}


void RepoNetworkAccessManager::fetchAvatar(const QString& username)
{
    reset();
    QNetworkReply *reply = this->get(getNetworkRequest(getURL(AVATAR, username)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyErrored(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(replySslErrored(QList<QSslError>)));
}

void RepoNetworkAccessManager::replyErrored(QNetworkReply::NetworkError error)
{
    qDebug() << "Qt error: " << error;
}

void RepoNetworkAccessManager::replySslErrored(QList<QSslError> list)
{
    qDebug() << "SSL Error: " << list;
}

void RepoNetworkAccessManager::processErrorNetworkReply(QNetworkReply* reply)
{
    // Eg: "code":"INCORRECT_USERNAME_OR_PASSWORD","message":"Incorrect
    // username or password","place":"POST /login","status":400,"value":2}
    QString replyString = (QString) reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(replyString.toUtf8());
    setProperty("lastErrorMessage", jsonDocument.object()["message"].toString());
    emit isError();
}

QUrl RepoNetworkAccessManager::getURL(API api, const QString &param)
{
    QString call;
    switch (api)
    {
    case LOGIN:
        call = "login";
        break;
    case LIST_INFO:
        call = param + ".json";
        break;
    case AVATAR :
        call = param + "/avatar";
        break;
    }
    return QUrl("https://" + targetServer + ".3drepo.io/api/" + call);
}

QNetworkRequest RepoNetworkAccessManager::getNetworkRequest(const QUrl &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    return request;
}
