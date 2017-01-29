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

QString repo::RepoDataMatrix::decode(const QImage &image, uint timeout)
{   
    return decode((unsigned char *) image.bits(),
                  image.width(),
                  image.height(),
                  getDataFormat(image.format()),
                  DmtxFlipNone);
}

QString repo::RepoDataMatrix::decode(
        unsigned char *bits,
        int width,
        int height,
        DmtxPackOrder format,
        DmtxFlip flip)
{
    QString message;
    int timeout = 100;
    DmtxImage *img = dmtxImageCreate(bits, width, height, format);
    dmtxImageSetProp(img, DmtxPropImageFlip, flip);

    if (img != NULL)
    {
        DmtxDecode *dec = dmtxDecodeCreate(img, 1);
        if (dec != NULL)
        {
            // usec is in microseconds while our timeout in milliseconds
            DmtxTime cutoffTime = dmtxTimeNow();
            cutoffTime.usec += timeout * 1000;

            // Cutoff time is an offset from now()
            DmtxRegion *reg = dmtxRegionFindNext(dec, &cutoffTime);
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

QString repo::RepoDataMatrix::decode(QVideoFrame *frame, bool flipped)
{
    QString message;
    if (frame->map(QAbstractVideoBuffer::ReadOnly))
    {
        // For whatever reason Windows flips the scanlines, see here:
        // https://forum.qt.io/topic/42967/video-on-streamingvideosurface-is-inverted-or-not-depending-on-whose-pc-runs-it
        message = decode(frame->bits(),
                         frame->width(),
                         frame->height(),
                         getDataFormat(frame->pixelFormat()),
                         flipped ? DmtxFlipY : DmtxFlipNone);

        frame->unmap();
    }
    return message;
}

DmtxPackOrder repo::RepoDataMatrix::getDataFormat(const QImage::Format &format)
{
    // See http://doc.qt.io/qt-5/qimage.html#Format-enum
    DmtxPackOrder packOrder;
    switch(format)
    {
    case QImage::Format_Mono : // The image is stored using 1-bit per pixel. Bytes are packed with the most significant bit (MSB) first.
    case QImage::Format_MonoLSB : // The image is stored using 1-bit per pixel. Bytes are packed with the less significant bit (LSB) first.
        packOrder = DmtxPack1bppK ;
        break;

    case QImage::Format_Alpha8 : // The image is stored using an 8-bit alpha only format.
    case QImage::Format_Grayscale8 : // The image is stored using an 8-bit grayscale format.
        packOrder = DmtxPack8bppK;
        break;

    case QImage::Format_RGB16 : // The image is stored using a 16-bit RGB format (5-6-5).
    case QImage::Format_RGB555 : // The image is stored using a 16-bit RGB format (5-5-5). The unused most significant bit is always zero.
    case QImage::Format_RGB444 : // The image is stored using a 16-bit RGB format (4-4-4). The unused bits are always zero.
        packOrder = DmtxPack16bppRGB;
        break;

    case QImage::Format_RGB888 : // The image is stored using a 24-bit RGB format (8-8-8).
    case QImage::Format_RGB666 : // The image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero.
        packOrder = DmtxPack24bppRGB;
        break;

    case QImage::Format_RGB32 : // The image is stored using a 32-bit RGB format (0xffRRGGBB).
    case QImage::Format_ARGB32 : // The image is stored using a 32-bit ARGB format (0xAARRGGBB).
        packOrder = DmtxPack32bppXRGB;
        break;

    default :
        packOrder = DmtxPackCustom;
        std::cerr << "Unspupported image format detected: " << format << std::endl;
        break;

    }
    return packOrder;
}

DmtxPackOrder repo::RepoDataMatrix::getDataFormat(const QVideoFrame::PixelFormat &format)
{
    // See http://doc.qt.io/qt-5/qvideoframe.html#PixelFormat-enum
    DmtxPackOrder packOrder;
    switch(format)
    {
    case QVideoFrame::Format_Y8 : // The frame is stored using an 8-bit greyscale format.
        packOrder = DmtxPack8bppK;
        break;

    case QVideoFrame::Format_RGB565 : // The frame is stored using a 16-bit RGB format (5-6-5). This is equivalent to QImage::Format_RGB16.
    case QVideoFrame::Format_RGB555 : // The frame is stored using a 16-bit RGB format (5-5-5). This is equivalent to QImage::Format_RGB555.
        packOrder = DmtxPack16bppRGB;
        break;

    case QVideoFrame::Format_BGR565 : // The frame is stored using a 16-bit BGR format (5-6-5).
    case QVideoFrame::Format_BGR555 : // The frame is stored using a 16-bit BGR format (5-5-5).
        packOrder = DmtxPack16bppBGR;
        break;

    case QVideoFrame::Format_RGB24 : // The frame is stored using a 24-bit RGB format (8-8-8). This is equivalent to QImage::Format_RGB888
    case QImage::Format_RGB666 : // The image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero.
        packOrder = DmtxPack24bppRGB;
        break;

    case QVideoFrame::Format_BGR24: // The frame is stored using a 24-bit BGR format (0xBBGGRR).
        packOrder = DmtxPack24bppBGR;
        break;

    case QVideoFrame::Format_YUV444 : // The frame is stored using a 24-bit packed YUV format (8-8-8).
        packOrder = DmtxPack24bppYCbCr;
        break;

    case QVideoFrame::Format_RGB32 : // The frame stored using a 32-bit RGB format (0xffRRGGBB). This is equivalent to QImage::Format_RGB32
    case QVideoFrame::Format_ARGB32 : // The frame is stored using a 32-bit ARGB format (0xAARRGGBB). This is equivalent to QImage::Format_ARGB32.
        packOrder = DmtxPack32bppXRGB;
        break;

    case QVideoFrame::Format_BGR32 : // The frame is stored using a 32-bit BGR format (0xBBGGRRff).
    case QVideoFrame::Format_BGRA32: // The frame is stored using a 32-bit BGRA format (0xBBGGRRAA).
        packOrder = DmtxPack32bppBGRX;
        break;

    default :
        packOrder = DmtxPackCustom;
        std::cerr << "Unspupported video format detected: " << format << std::endl;
        break;
    }
    return packOrder;
}
