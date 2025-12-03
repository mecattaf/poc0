#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick/QtWebEngineQuick>
#include <QWebChannel>
#include <QQmlContext>

#include "CoreService.h"

int main(int argc, char *argv[])
{
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Create the CoreService
    CoreService coreService;

    // Create the WebChannel and register the service
    QWebChannel channel;
    channel.registerObject(QStringLiteral("coreService"), &coreService);

    // Expose the channel to QML so it can be passed to the WebEngineView
    engine.rootContext()->setContextProperty("webChannel", &channel);

    const QUrl url(QStringLiteral("qrc:/resources/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
