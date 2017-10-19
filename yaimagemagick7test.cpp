#include "yaimagemagick7test.h"
#include <QDebug>
#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>

YaImageMagick7Test::YaImageMagick7Test(QObject *parent) : QObject(parent)
{

}

YaImageMagick7Test::~YaImageMagick7Test()
{

}
void
YaImageMagick7Test::getResources()
{

}

void
YaImageMagick7Test::removeResources()
{

}

bool
YaImageMagick7Test::testCore()
{
    MagickCoreGenesis((char *) NULL,MagickFalse);
    qDebug() << "magickCore is OK";
    MagickCoreTerminus();

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
