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

#include "repo_data_matrix_image_provider.h"

QPixmap repo::RepoDataMatrixImageProvider::requestPixmap(
        const QString &id,
        QSize *size,
        const QSize & /*requestedSize*/)
{
    QPixmap pixmap;
    if (!id.isEmpty())
    {
        QImage dataMatrix = RepoDataMatrix::encode(id);
        if (size)
            *size = dataMatrix.size();
        pixmap = QPixmap::fromImage(dataMatrix);
    }
    return pixmap;
}
