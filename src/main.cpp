#include <QGuiApplication>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <qwlogging.h>
#include <wserver.h>
#include <wrenderhelper.h>

#include "compositor.h"

int main(int argc, char *argv[])
{
    // Phase 1: Qt attributes for WebEngine (BEFORE QGuiApplication)
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    // Phase 2: WebEngine initialization (BEFORE QGuiApplication)
    QtWebEngineQuick::initialize();

    // Phase 3: wlroots/waylib initialization (BEFORE QGuiApplication)
    qw_log::init();
    WRenderHelper::setupRendererBackend();
    WServer::initializeQPA();

    // Configure Qt application
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setQuitOnLastWindowClosed(false);

    QGuiApplication app(argc, argv);

    // Create and start compositor
    Compositor compositor;
    if (!compositor.start()) {
        qCritical() << "Failed to start compositor";
        return -1;
    }

    qInfo() << "Entering event loop...";
    return app.exec();
}
