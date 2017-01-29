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

#include "repo_data_matrix.h"


QImage repo::RepoDataMatrix::encode(const QString &text)
{
    QImage image;
    DmtxEncode *enc = dmtxEncodeCreate();
    if (enc != NULL)
    {
        // ENCODE a new Data Matrix barcode image (in memory only)
        dmtxEncodeDataMatrix(enc, (int) text.toStdString().size(),
                             (unsigned char*) text.toStdString().c_str());

        // COPY the new image data before releasing encoding memory
        int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
        int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
        int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);

        // Instatiate and populate the return QImage.
        image = QImage(width, height, QImage::Format_RGB888);
        unsigned char *bits = (unsigned char*) image.bits();
        memcpy(bits, enc->image->pxl, width * height * bytesPerPixel);

        dmtxEncodeDestroy(&enc);
    }
    return image;
}

QString repo::RepoDataMatrix::decode(const QImage &image)
{
    QString message;
    std::cout << "Format: " << image.format() << std::endl;

    // TODO Image format
    DmtxImage *img = dmtxImageCreate((unsigned char *) image.bits(),
                                     image.width(),
                                     image.height(),
                                     DmtxPack32bppXRGB); // DmtxPack24bppRGB);
    if (img != NULL)
    {
        DmtxDecode *dec = dmtxDecodeCreate(img, 1);
        if (dec != NULL)
        {

            DmtxTime timeout = dmtxTimeNow();
            timeout.usec += 100000;
            DmtxRegion *reg = dmtxRegionFindNext(dec, &timeout);

            if (reg != NULL)
            {
                DmtxMessage *msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
                if(msg != NULL)
                {
                    message = QString::fromUtf8((const char*) msg->output);
                    dmtxMessageDestroy(&msg);
                }
                dmtxRegionDestroy(&reg);
            }
            dmtxDecodeDestroy(&dec);
        }
        dmtxImageDestroy(&img);
    }
    return message;
}
