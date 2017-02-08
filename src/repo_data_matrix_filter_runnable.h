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

#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <QMutex>

#include "repo_data_matrix_filter_result.h"
#include "repo_data_matrix_filter.h"
#include "repo_data_matrix.h"

#include <iostream>

namespace repo {

// See https://blog.qt.io/blog/2015/03/20/introducing-video-filters-in-qt-multimedia/
class RepoDataMatrixFilterRunnable : public QVideoFilterRunnable
{

public:

    RepoDataMatrixFilterRunnable(RepoDataMatrixFilter *filter);

    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) Q_DECL_OVERRIDE;

private :

    RepoDataMatrixFilter* filter;

    QMutex mutex;
};
}

