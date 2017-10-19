#ifndef YAIMAGEMAGICK7TEST_H
#define YAIMAGEMAGICK7TEST_H

#include <QObject>

class YaImageMagick7Test : public QObject
{
    Q_OBJECT
public:
    explicit YaImageMagick7Test(QObject *parent = nullptr);
    ~YaImageMagick7Test();
    void getResources();
    void removeResources();
    bool testCore();
    bool testWand();

signals:

public slots:
};

#endif // YAIMAGEMAGICK7TEST_H
