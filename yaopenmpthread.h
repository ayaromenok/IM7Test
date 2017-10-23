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

signals:
    void resultReady(const QString &s);
private:
    QString     _omp;
    QStringList _ompList;
};

#endif // YAOPENMPTHREAD_H
