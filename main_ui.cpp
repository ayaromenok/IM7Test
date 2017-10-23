#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QDebug>

#include "yaprogramversion.h"
#include "yaimagemagick7test.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //qmlRegisterType<YaImageMagick7Test> ("MagickTest", 1, 0, "MTest");
    qDebug() << "ImageMagick 7 test app/GUI";

//    YaProgramVersion pv;
//    pv.toConsole(false);

    YaImageMagick7Test imt;
    imt.getResources();
    imt.testCore();
    imt.testWand();
//    imt.removeResources();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main_ui.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    QObject::connect(window, SIGNAL(sigTestAll(QString)),
                     &imt, SLOT(testOmpAll(QString)));

    QObject::connect(&imt, SIGNAL(testOmpAutoChanged(QVariant)),
                     window, SLOT(fnTestOmpAuto(QVariant)));
    QObject::connect(&imt, SIGNAL(testOmpOneChanged(QVariant)),
                     window, SLOT(fnTestOmpOne(QVariant)));
    QObject::connect(&imt, SIGNAL(testOmpTwoChanged(QVariant)),
                     window, SLOT(fnTestOmpTwo(QVariant)));
    QObject::connect(&imt, SIGNAL(testOmpFourChanged(QVariant)),
                     window, SLOT(fnTestOmpFour(QVariant)));
    QObject::connect(&imt, SIGNAL(testOmpEightChanged(QVariant)),
                     window, SLOT(fnTestOmpEight(QVariant)));

    return app.exec();
}
