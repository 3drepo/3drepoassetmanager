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

#include "repo_data_matrix_filter_runnable.h"

repo::RepoDataMatrixFilterRunnable::RepoDataMatrixFilterRunnable(
        RepoDataMatrixFilter *filter)
{
    this->filter = filter;
}

QVideoFrame repo::RepoDataMatrixFilterRunnable::run(
        QVideoFrame *input,
        const QVideoSurfaceFormat &surfaceFormat,
        RunFlags flags)
{
    RepoDataMatrixFilterResult *result = new RepoDataMatrixFilterResult;
    result->_resolution = input->size();

    if (mutex.tryLock(0)) // drop frames
    {
        bool flipped = surfaceFormat.scanLineDirection() == QVideoSurfaceFormat::BottomToTop;
        QPair<QString, QRect> res = RepoDataMatrix::decode(input, flipped);
        result->_message = res.first;
        result->_rectangle = res.second;
        mutex.unlock();
    }

    emit filter->finished(result);
    return *input;
}
