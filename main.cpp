#include <QCoreApplication>
#include <QDebug>
#include "yaprogramversion.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "ImageMagick 7 test app/console";

    YaProgramVersion pv;
    pv.toConsole(false);

    return a.exec();
}
