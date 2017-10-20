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

    return true;
}

bool
YaImageMagick7Test::testWand()
{
    MagickWand *magickWand;
    MagickWandGenesis();
    magickWand = NewMagickWand();
    qDebug() << "magickWand is OK";
    magickWand = DestroyMagickWand(magickWand);
    MagickWandTerminus();
    return true;
}
