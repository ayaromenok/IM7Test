#include <QCoreApplication>
#include <QDebug>
#include "yaprogramversion.h"
#include "yaimagemagick7test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "ImageMagick 7 test app/console";

    YaProgramVersion pv;
    pv.toConsole(false);

    YaImageMagick7Test imt;
    imt.getResources();
    imt.testCore();
    imt.testWand();
    imt.removeResources();

    return a.exec();
}
