#include "yaim7test.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTime>
#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>

YaIM7Test::YaIM7Test(bool isUI, int maxNumOfThreads)
{
    _isUI = isUI;
    _maxNumOfThreads = maxNumOfThreads;
    qDebug() << "UI:" << _isUI << "max # of threads" << _maxNumOfThreads;
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
    _testList.append(QString(_resList.at(0)).replace(0, 4, "./res/core_"));
    _testList.append(QString(_resList.at(0)).replace(0, 4, "./res/wand_"));
    _testList.append(QString(_resList.at(0)).replace(0, 4, "./res/opencl_"));
    for (int i=0; i<=_maxNumOfThreads; i++)     // 0 is Auto + # of threads
        _testList.append(QString(_resList.at(0)).replace(0, 4,
                                      ("./res/openmp"+QString::number(i)+"_")));

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
    for (int i=0; i<_testList.size(); i++){
        file.setFileName("./"+_testList.at(i));
        if(file.remove())
            qDebug() << "removed:" << _testList.at(i);
        else
            qDebug() << "can't remove:" << _testList.at(i);
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


    //just a simple rotate
    imagew = IntegralRotateImage(image,1,exception);

    _result = t.elapsed();
    qDebug() << "core: image rotated:" << _result << "msec";
    if (writeToFile) {
        ImageInfo *write_info;
        MagickBooleanType status;

        write_info=CloneImageInfo(read_info);
        CopyMagickString(write_info->filename,
                         _testList.at(0).toLatin1().constData(), MaxTextExtent);
        status=WriteImages(write_info, imagew, write_info->filename,exception);
        if (status == MagickFalse)
            qCritical() << "can't write to" << _testList.at(0);
        DestroyImageInfo(write_info);
    }
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
    MagickWand *magick_wand;
    PixelWand *background = NewPixelWand();
    MagickBooleanType status;

    MagickWandGenesis();

    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand,_resList.at(0).toLatin1());
    if (status == MagickFalse)
        qCritical() <<"can't read from" << _resList.at(0);

    QTime t;
    t.start();

    //just simple rotate. after caching should be the same, as core result
    MagickRotateImage(magick_wand,background,90);

    _result = t.elapsed();
    qDebug() << "wand: image rotated:"<<_result << "msec";
    if (writeToFile) {
        status = MagickWriteImage(magick_wand, _testList.at(1).toLatin1());
        if (status == MagickFalse)
            qCritical() << "can't write to" << _testList.at(1);
    }

    background = DestroyPixelWand(background);
    magick_wand = DestroyMagickWand(magick_wand);

    MagickWandTerminus();

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
