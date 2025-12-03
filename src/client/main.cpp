#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    // Phase 1: Set Qt attributes for WebEngine
    // These are critical for WebEngine to work properly
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    
    // Initialize WebEngine BEFORE QGuiApplication
    QtWebEngineQuick::initialize();

    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("web-shell");
    QGuiApplication::setApplicationDisplayName("Web Shell");

    QQmlApplicationEngine engine;
    
    // Load the main QML file
    const QUrl url(QStringLiteral("qrc:/qt/qml/WebShell/client/qml/main.qml"));
    
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
