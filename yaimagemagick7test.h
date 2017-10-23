#ifndef YAIMAGEMAGICK7TEST_H
#define YAIMAGEMAGICK7TEST_H

#include <QObject>
#include <QVariant>

class YaImageMagick7Test : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int testOmpAuto READ testOmpAuto NOTIFY testOmpAutoChanged)
    Q_PROPERTY(int testOmpOne READ testOmpOne NOTIFY testOmpOneChanged)
    Q_PROPERTY(int testOmpTwo READ testOmpTwo NOTIFY testOmpTwoChanged)
    Q_PROPERTY(int testOmpFour READ testOmpFour NOTIFY testOmpFourChanged)
    Q_PROPERTY(int testOmpEight READ testOmpEight NOTIFY testOmpEightChanged)
public:
    explicit YaImageMagick7Test(QObject *parent = nullptr);
    ~YaImageMagick7Test();
    void getResources();
    void removeResources();
    bool testCore();
    bool testWand();

signals:
    void testOmpAutoChanged(QVariant result);
    void testOmpOneChanged(QVariant result);
    void testOmpTwoChanged(QVariant result);
    void testOmpFourChanged(QVariant result);
    void testOmpEightChanged(QVariant result);

public slots:
    int testOmpAuto(){runOmpAuto(); return _resultOmpAuto;}
    int testOmpOne(){runOmpOne(); return _resultOmpOne;}
    int testOmpTwo(){runOmpTwo(); return _resultOmpTwo;}
    int testOmpFour(){runOmpFour(); return _resultOmpFour;}
    int testOmpEight(){runOmpEight(); return _resultOmpEight;}
    void testOmpAll(QString value);
    void threadTest(QString result);

private:
    void        runOmpAuto();
    void        runOmpOne();
    void        runOmpTwo();
    void        runOmpFour();
    void        runOmpEight();

    void        sleep(int msec);
    QString     _testImagePath;
    quint32     _numOfOmpThreads;
    int         _testResult; //in msec
    quint32     _imgWidth;
    quint32     _imgHeight;
    int         _resultOmpAuto;
    int         _resultOmpOne;
    int         _resultOmpTwo;
    int         _resultOmpFour;
    int         _resultOmpEight;

    QString     _omp;
};

#endif // YAIMAGEMAGICK7TEST_H
