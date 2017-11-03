#include "yaim7test.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTime>
#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>

YaIM7Test::YaIM7Test(bool isUI)
{
    _isUI = isUI;
    qDebug() << "UI:" << _isUI;
}

YaIM7Test::~YaIM7Test()
{

}

void
YaIM7Test::getResources()
{
    QDir    dir;
    QFile   file;
    _resList.clear();
    if (getResourcesList())
    {
        qDebug() << "extract resources here"<<_resList;
        dir.mkdir("res");
        for (int i=0; i<_resList.size(); i++){
            file.setFileName("./"+_resList.at(i));
            if(file.remove())
                qDebug() << "removed:" << _resList.at(i);
            else
                qDebug() << "can't remove:" << _resList.at(i);
            file.setFileName(":/"+_resList.at(i));
            if (file.copy("./"+_resList.at(i)))
                qDebug() << "extracted:" << _resList.at(i);
            else
                qDebug() << "can't extract:" << _resList.at(i);
        }
    }
}

void
YaIM7Test::removeResources()
{
    QDir    dir;
    QFile   file;
    qDebug() << "remove resources here:" << _resList;

    for (int i=0; i<_resList.size(); i++){
        file.setFileName("./"+_resList.at(i));
        if(file.remove())
            qDebug() << "removed:" << _resList.at(i);
        else
            qDebug() << "can't remove:" << _resList.at(i);
    }
    dir.remove("res");
}

bool
YaIM7Test::testCore(bool writeToFile)
{
    qDebug() << "testCore, write to file:" << writeToFile;
    Image *image, *imagew;
    ImageInfo *read_info;
    ExceptionInfo *exception;
    QTime t;

    MagickCoreGenesis((char *) NULL,MagickFalse);

    exception = AcquireExceptionInfo();
    read_info=CloneImageInfo(NULL);
    CopyMagickString(read_info->filename, _resList.at(0).toLatin1().constData(),
                     MaxTextExtent);
    image = ReadImage(read_info,exception);t.start();
    imagew = IntegralRotateImage(image,1,exception);
    _result = t.elapsed();
    qDebug() << "image rotated:" << _result << "msec";
    DestroyImage(imagew);
    DestroyImage(image);
    DestroyImageInfo(read_info);
    DestroyExceptionInfo(exception);

    MagickCoreTerminus();

    return true;
}

bool
YaIM7Test::testWand(bool writeToFile)
{
    qDebug() << "testWand, write to file:" << writeToFile;
    return true;
}

int
YaIM7Test::testOpenMP(int numOfThreads, bool writeToFile)
{
    qDebug() << "testOpenMP, #:" << numOfThreads
             <<", write to file:" << writeToFile;
    if (numOfThreads >=0)
        _result = 42;
    return _result;
}

bool
YaIM7Test::getResourcesList()
{
    QFile file;
    if (_isUI)
        file.setFileName(":/res/resourcesUI.txt");
    else
        file.setFileName(":/res/resourcesConsole.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString str;
        while (!file.atEnd()) {
            str.clear();
            str.append(file.readLine());
            _resList.append(str.remove((str.length()-1), 1));
        }
    } else {
        qCritical() << "file not found" << file.fileName();
        return false;
    }
    return true;
}
