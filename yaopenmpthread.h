#ifndef YAOPENMPTHREAD_H
#define YAOPENMPTHREAD_H
#include <QObject>
#include <QVariant>
#include <QThread>

class YaOpenMPThread : public QThread
{
    Q_OBJECT
    void run() override;
public:
    void setOpenMP(QString value);
    void setTestImage(QString path){_testImage.clear(); _testImage.append(path);}
    void setWriteToFile(bool value) {_isWriteToFile = value;}

signals:
    void resultReady(const QString &s);
private:
    int runTestOMP(int numOfThreads);

    QString     _omp;
    QStringList _ompList;
    QString     _testImage;
    int         _result;
    int         _numOfThreads;
    bool        _isWriteToFile;

};

#endif // YAOPENMPTHREAD_H
