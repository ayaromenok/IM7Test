#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "yaprogramversion.h"
#include "yaimagemagick7test.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<YaImageMagick7Test> ("MagickTest", 1, 0, "MTest");
    qDebug() << "ImageMagick 7 test app/GUI";

    YaProgramVersion pv;
    pv.toConsole(false);

//    YaImageMagick7Test imt;
//    imt.getResources();
//    imt.testCore();
//    imt.testWand();
//    imt.removeResources();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main_ui.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
