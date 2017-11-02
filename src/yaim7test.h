#ifndef YAIM7TEST_H
#define YAIM7TEST_H

#include <QObject>

class YaIM7Test : public QObject
{
    Q_OBJECT
public:
    explicit YaIM7Test(bool isUI = false);
    ~YaIM7Test();
    void getResources();
    void removeResources();
    bool testCore(bool writeToFile = false);
    bool testWand(bool writeToFile = false);

signals:

public slots:

private:
    bool            getResourcesList();
    bool            _isUI;
    QStringList     _resList;
};

#endif // YAIM7TEST_H
