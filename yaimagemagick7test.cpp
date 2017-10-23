#include "yaimagemagick7test.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTime>

#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>


YaImageMagick7Test::YaImageMagick7Test(QObject *parent) : QObject(parent)
{
    _numOfOmpThreads = 0;
}

YaImageMagick7Test::~YaImageMagick7Test()
{

}
void
YaImageMagick7Test::getResources()
{
    QDir        dir;
    //QFile     file(":/res/testScene2048x2048.png");
    QFile       file(":/res/lena_hires.png");
    QString     testImageName("testImage.png");

    _testImagePath.clear();

    if (file.open(QIODevice::ReadOnly)){
        file.copy(QString("./"+testImageName));
        _testImagePath.append(dir.currentPath());
        _testImagePath.append("/");
        _testImagePath.append(testImageName);
        file.setFileName(_testImagePath);
        if (file.exists()) {
            qDebug() << "test image extracted to" << _testImagePath;
        } else {
            qCritical() << "can't extract test image" << testImageName;
        }
    }
}

void
YaImageMagick7Test::removeResources()
{
    qDebug() << "YaImageMagick7Test::removeRes()";
    QFile file(_testImagePath);
    if (file.exists())
        file.remove();

    QString _fNameCore(_testImagePath);
    _fNameCore.replace(".png","_Core.png");
    file.setFileName(_fNameCore);
    if (file.exists())
        file.remove();

    QString _fNameWand(_testImagePath);
    _fNameWand.replace(".png","_Wand.png");
    file.setFileName(_fNameWand);
    if (file.exists())
        file.remove();

    for (int i=0; i<_numOfOmpThreads; i++ )
    {
        QString pathRW(_testImagePath);
        QString newName("_OpenMP_");
        newName.append(QString::number(i));
        newName.append(".png");
        pathRW.replace(".png",newName);
        file.setFileName(pathRW);
        if (file.exists())
            file.remove();
    }

    _testImagePath.clear();
}

bool
YaImageMagick7Test::testCore()
{
    QString pathRW(_testImagePath);
    QFile file(_testImagePath);
    if (file.exists()) {
    Image *image,*imagew;
    ImageInfo *read_info;
    ImageInfo *write_info;
    ExceptionInfo *exception;
    MagickBooleanType status;

    MagickCoreGenesis((char *) NULL,MagickFalse);

    exception = AcquireExceptionInfo();

    read_info=CloneImageInfo(NULL);
    CopyMagickString(read_info->filename, pathRW.toLatin1().constData(),
                     MaxTextExtent);
    image = ReadImage(read_info,exception);
    _imgWidth = image->columns;
    _imgHeight = image->rows;
    pathRW.replace(".png","_Core.png");
    QFile file(pathRW);
    if (file.exists())
        file.remove();      //remove from previous iteration

    qDebug() << "MagickCore/rotate\t" << _imgWidth << "x" << _imgHeight
             << "image at\t" << pathRW;

    QTime t;
    t.start();
    imagew = IntegralRotateImage(image,1,exception);
    _testResult = t.elapsed();

    qDebug() << "\nresult:" << _testResult << "msec\n";

    write_info=CloneImageInfo(read_info);
    CopyMagickString(write_info->filename, pathRW.toLatin1().constData(),
                     MaxTextExtent);
    status=WriteImages(write_info, imagew, write_info->filename,exception);

    DestroyImage(imagew);
    DestroyImageInfo(write_info);
    DestroyImage(image);
    DestroyImageInfo(read_info);

    DestroyExceptionInfo(exception);

    MagickCoreTerminus();
    }
    else {
        qCritical() << "test resources missed";
        return false;
    }

    return true;
}

bool
YaImageMagick7Test::testWand()
{
    QString pathRW(_testImagePath);

    MagickBooleanType status;
    MagickWand *magick_wand;
    PixelWand *background = NewPixelWand();
    Image *imagew;

    MagickWandGenesis();

    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand,pathRW.toLatin1());
    if (status == MagickFalse)
        qDebug() <<"wrong";

    pathRW.replace(".png","_Wand.png");
    QFile file(pathRW);
    if (file.exists())
        file.remove();      //remove from previous iteration

    qDebug() << "MagickWand/rotate\t" << _imgWidth << "x" << _imgHeight
             << "image at\t" << pathRW;

    QTime t;
    t.start();
    MagickRotateImage(magick_wand,background,90);
    _testResult = t.elapsed();
    qDebug() << "\nresult:"<<_testResult << "msec\t";

    status = MagickWriteImage(magick_wand,pathRW.toLatin1());
    if (status == MagickFalse)
        qDebug() <<"wrong again";

    background = DestroyPixelWand(background);
    magick_wand = DestroyMagickWand(magick_wand);

    MagickWandTerminus();
    return true;
}


void
YaImageMagick7Test::runOmpAuto()
{
    qDebug() << "runOmpAuto()";
    _resultOmpAuto = 1248;
}


void
YaImageMagick7Test::runOmpOne()
{
    qDebug() << "runOmpOne()";
    _resultOmpOne = 10;
}


void
YaImageMagick7Test::runOmpTwo()
{
    qDebug() << "runOmpTwo()";
    _resultOmpTwo = 20;
}


void
YaImageMagick7Test::runOmpFour()
{
    qDebug() << "runOmpFour()";
    _resultOmpFour = 40;
}

void
YaImageMagick7Test::runOmpEight()
{
    qDebug() << "runOmpEight()";
    _resultOmpEight = 80;
}
