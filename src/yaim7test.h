#ifndef YAIM7TEST_H
#define YAIM7TEST_H

#include <QObject>

class YaIM7Test : public QObject
{
    Q_OBJECT
public:
    explicit YaIM7Test(bool isUI = false, int maxNumOfThreads = 20);
    ~YaIM7Test();
    void    getResources();
    void    removeResources();
    bool    testCore(bool writeToFile = false);
    bool    testWand(bool writeToFile = false);
    int     testOpenMP(int numOfThreads, bool writeToFile = false);

signals:

public slots:

private:
    bool            getResourcesList();
    bool            _isUI;
    int             _result; //msec, enough for few hundred seconds
    int             _maxNumOfThreads;
    QStringList     _resList;
    QStringList     _testList;
};

#endif // YAIM7TEST_H
