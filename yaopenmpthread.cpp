#include <QDebug>
#include "yaopenmpthread.h"

void
YaOpenMPThread::run()
{
    QString result("res");
    QStringList ompList(_omp.split(' '));
    int msec = 500;
    struct timespec ts = { msec / 1000, (msec % 1000) * 1000 * 1000 };
    for (int i=0; i<ompList.length(); i++){
        result.clear();
        nanosleep(&ts, NULL);
        int k = ompList.at(i).toInt();
        result.append(ompList.at(i));
        result.append(" ");
        result.append(QString::number(msec*k));
        emit resultReady(result);
    }
}

void
YaOpenMPThread::setOpenMP(QString value) {
    _omp.clear();
    _omp.append(value);
}
