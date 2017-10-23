#ifndef YAIMAGEMAGICK7TEST_H
#define YAIMAGEMAGICK7TEST_H

#include <QObject>

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

    int testOmpAuto(){runOmpAuto(); return _resultOmpAuto;}
    int testOmpOne(){runOmpOne(); return _resultOmpOne;}
    int testOmpTwo(){runOmpTwo(); return _resultOmpTwo;}
    int testOmpFour(){runOmpFour(); return _resultOmpFour;}
    int testOmpEight(){runOmpEight(); return _resultOmpEight;}

signals:
    void testOmpAutoChanged();
    void testOmpOneChanged();
    void testOmpTwoChanged();
    void testOmpFourChanged();
    void testOmpEightChanged();
public slots:

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
};

#endif // YAIMAGEMAGICK7TEST_H
