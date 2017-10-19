#include "yaprogramversion.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

YaProgramVersion::YaProgramVersion(QObject *parent) : QObject(parent)
{
    QFile file(":/program_version.txt");
    if (file.open(QIODevice::ReadOnly)){
        QTextStream qts(&file);
        quint32 line = 0;
        while(!qts.atEnd()) {
            if (line == 0)
                _tag.append(qts.readLine());
            else if (line == 1)
                _count.append(qts.readLine());
            else if (line == 2)
                _branch.append(qts.readLine());
            else {
                _lastCommit.append(qts.readLine());
                _lastCommit.append(" ");
            }
            line++;
        }
    }
}

void
YaProgramVersion::toConsole(bool showLastCommit)
{
    qInfo() << "\tbranch:" << _branch;
    qInfo() << "\ttag:" << _tag;
    qInfo() << "\t#:" << _count;
    if (showLastCommit)
        qInfo() << "last" << _lastCommit;
}
