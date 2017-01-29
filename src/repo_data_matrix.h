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
#include <QImage>
#include <QString>
#include <QVideoFrame>

#include "dmtx.h"

#include <iostream>

namespace repo
{

/**
 * Static class which provides encoding and decoding functions for Data Matrix
 * specification based on Libdmtx library.
 *
 * Libdmtx: http://libdmtx.sourceforge.net
 * See also: http://libdmtx.sourceforge.net/display.php?text=libdmtx.3
 *
 * @brief The RepoDataMatrix class
 */
class RepoDataMatrix : public QObject
{
    Q_OBJECT

public slots:

    /**
     * Encodes given string as a data matrix image formatted in
     * QImage::Format_RGB888.
     * @brief encode
     * @param text
     * @return
     */
    static QImage encode(const QString &text);

    /**
     * Decodes given image into a message. Returns empty string if
     * no text can be found within given timeout.
     *
     * @brief decode
     * @param image
     * @param timeout in milliseconds
     * @return
     */
    static QString decode(const QImage &image, uint timeout = 10);

    static QString decode(QVideoFrame *input, bool flipped = false);

    static QString decode(unsigned char *bits, int width, int height, DmtxPackOrder format, DmtxFlip flip = DmtxFlipNone);

    /**
     * Given a QImage returns pixel packing format suitable for Libdmtx decoding.
     * @brief getImageFormat
     * @param image
     * @return
     */
    static DmtxPackOrder getDataFormat(const QImage::Format &format);

    static DmtxPackOrder getDataFormat(const QVideoFrame::PixelFormat &format);
};

}

