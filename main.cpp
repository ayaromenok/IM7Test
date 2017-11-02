#include <QCoreApplication>
#include <QDebug>
#include "yaprogramversion.h"
#include "src/yaim7test.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "ImageMagick 7 test app/console";

    YaProgramVersion pv;
    pv.toConsole(true);

    YaIM7Test imt;
    imt.getResources();
    imt.testCore(true);
    imt.testWand(true);
    imt.removeResources();

    return a.exec();
}
