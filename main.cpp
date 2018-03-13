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
    //don't save results for test
    imt.testCore(false);
    imt.testWand(false);
    imt.testOpenMP(0, false);// warm up
    imt.testOpenMP(0, false);
    imt.testOpenMP(1, false);
    imt.testOpenMP(2, false);
    imt.testOpenMP(4, false);
    imt.testOpenMP(8, false);
    //disable OpenCL test too
    //imt.testOpenCL(true, true);
    //imt.testOpenCL(false, true);
    //imt.removeResources(); //\todo switch ON later

    return a.exec();
}
