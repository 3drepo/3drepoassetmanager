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
#include <QRect>

namespace repo
{

class RepoDataMatrixFilterResult : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString message READ message)

    Q_PROPERTY(QRect rectangle READ rectangle)

    Q_PROPERTY(QSize resolution READ resolution)

public:

    QString message() const;

    QRect rectangle() const;

    QSize resolution() const;

private:

    QString _message;

    QRect _rectangle;

    QSize _resolution;

    friend class RepoDataMatrixFilterRunnable;
};
}
