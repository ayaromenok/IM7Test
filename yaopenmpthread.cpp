#include <QDebug>
#include <QFile>
#include <QTime>

#include "yaopenmpthread.h"

#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>

void
YaOpenMPThread::run()
{
    QString result("res");
    QStringList ompList(_omp.split(' '));
    for (int i=0; i<ompList.length(); i++){
        result.clear();
        int k = ompList.at(i).toInt();
        _result = runTestOMP(k);
        result.append(ompList.at(i));
        result.append(" ");
        result.append(QString::number(_result));
        emit resultReady(result);
    }
}

void
YaOpenMPThread::setOpenMP(QString value)
{
    _omp.clear();
    _omp.append(value);
}

int
YaOpenMPThread::runTestOMP(int numOfThreads)
{
    qDebug() << "YaOpenMPThread::runTestOMP(), threads" << numOfThreads;
    _result = 0;
    QString sNumOfThreads(QString::number(numOfThreads));

    if (numOfThreads > 0) //0 is auto in term of app(for magick 0 is equal to 1)
        qputenv("MAGICK_THREAD_LIMIT",sNumOfThreads.toLatin1());

    QString pathRW(_testImage);
    QString newName("_OpenMP_");

    Image *image,*imagew;
    ImageInfo *read_info;
    ExceptionInfo *exception;

    double*         m_lensArguments;
    m_lensArguments = (double *) AcquireQuantumMemory(3,sizeof(*m_lensArguments));
    m_lensArguments[0] = 0.012;
    m_lensArguments[1] = -0.11;
    m_lensArguments[2] = 0.12;

    MagickCoreGenesis((char *) NULL,MagickFalse);

    exception = AcquireExceptionInfo();

    read_info=CloneImageInfo(NULL);
    CopyMagickString(read_info->filename, pathRW.toLatin1().constData(),
                     MaxTextExtent);
    image = ReadImage(read_info,exception);

    QTime t;
    t.start();
    imagew = DistortImage(image, BarrelDistortion,
                          3, m_lensArguments, MagickFalse,
                          exception);
    _result = t.elapsed();

    if (_isWriteToFile) {
        ImageInfo *write_info;
        MagickBooleanType status;

        newName.append(QString::number(numOfThreads));
        newName.append(".png");
        pathRW.replace(".png",newName);
        QFile file(pathRW);
        if (file.exists())
            file.remove();      //remove from previous iteration

        write_info=CloneImageInfo(read_info);
        CopyMagickString(write_info->filename, pathRW.toLatin1().constData(),
                         MaxTextExtent);
        status=WriteImages(write_info, imagew, write_info->filename,exception);
        DestroyImageInfo(write_info);
    }
    qDebug() << "OpenMP/distort\t" << imagew->columns << "x" << imagew->rows
             << "image at\t" << _result << "msec\t"<< "threads" << numOfThreads;

    delete m_lensArguments;

    DestroyImage(imagew);

    DestroyImage(image);
    DestroyImageInfo(read_info);

    DestroyExceptionInfo(exception);

    MagickCoreTerminus();

    qunsetenv("MAGICK_THREAD_LIMIT");


    return _result;
}
