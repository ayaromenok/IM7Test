#include "yaim7test.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTime>

YaIM7Test::YaIM7Test(bool isUI)
{
    _isUI = isUI;
    qDebug() << "UI:" << _isUI;
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
    dir.remove("res");
}

bool
YaIM7Test::testCore(bool writeToFile)
{
    qDebug() << "testCore, write to file:" << writeToFile;
    return true;
}

bool
YaIM7Test::testWand(bool writeToFile)
{
    qDebug() << "testWand, write to file:" << writeToFile;
    return true;
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
