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
    setLastErrorMessage(QString());
}


void RepoNetworkAccessManager::authenticate(
        const QString& username,
        const QString &password)
{
    reset();

    this->username = username;

    QUrlQuery postData;
    postData.addQueryItem("username", username);
    postData.addQueryItem("password", password);


    QNetworkReply *reply = this->post(getNetworkRequest(getURL(LOGIN)),
                                      postData.toString(QUrl::FullyEncoded).toUtf8());
//    connect(reply, SIGNAL(readyRead()), this, SLOT(replyReady()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyErrored(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(replySslErrored(QList<QSslError>)));
}

void RepoNetworkAccessManager::finishedSlot(QNetworkReply* reply)
{
    QUrl url = reply->url();

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
            getUserInfo(username);
         }
        else if (url == getURL(LIST_INFO, username))
        {
            QString replyString = (QString) reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(replyString.toUtf8());
//            QString message = jsonDocument.object()["message"].toString();

            qDebug() << " ";
            qDebug() << " ";

            qDebug() << jsonDocument;
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


void RepoNetworkAccessManager::getUserInfo(const QString& username)
{
    reset();
    QNetworkReply *reply = this->get(getNetworkRequest(getURL(LIST_INFO, username)));
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

void RepoNetworkAccessManager::replyReady()
{
        qDebug() << "Reply ready";
}

void RepoNetworkAccessManager::setLastErrorMessage(const QString &msg)
{
    if (_lastErrorMessage != msg)
    {
        _lastErrorMessage = msg;
        emit lastErrorMessageChanged(_lastErrorMessage);
    }
}

QString RepoNetworkAccessManager::getLastErrorMessage() const
{
    return _lastErrorMessage;
}

void RepoNetworkAccessManager::processErrorNetworkReply(QNetworkReply* reply)
{
    // Eg: "code":"INCORRECT_USERNAME_OR_PASSWORD","message":"Incorrect
    // username or password","place":"POST /login","status":400,"value":2}
    QString replyString = (QString) reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(replyString.toUtf8());
    QString message = jsonDocument.object()["message"].toString();
    this->setLastErrorMessage(message);
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
