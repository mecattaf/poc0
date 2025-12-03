#include <QGuiApplication>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <qwlogging.h>
#include <wserver.h>
#include <wrenderhelper.h>

WAYLIB_SERVER_USE_NAMESPACE

#include "compositor.h"

int main(int argc, char *argv[])
{
    // Phase 1: Set Qt attributes BEFORE creating QGuiApplication
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setQuitOnLastWindowClosed(false);

    // Phase 2: Initialize platform integration BEFORE QGuiApplication
    // WServer::initializeQPA() sets up Qt Platform Abstraction for Wayland
    // and MUST be called before QGuiApplication is created
    qw_log::init();
    WRenderHelper::setupRendererBackend();
    WServer::initializeQPA();

    // Phase 3: Create QGuiApplication AFTER platform is initialized
    QGuiApplication app(argc, argv);

    // Phase 4: Initialize QtWebEngine AFTER QGuiApplication exists
    // Note: This will produce a deprecation warning but is functionally correct
    QtWebEngineQuick::initialize();

    // Create and start compositor
    Compositor compositor;
    if (!compositor.start()) {
        qCritical() << "Failed to start compositor";
        return -1;
    }

    qInfo() << "Entering event loop...";
    return app.exec();
}
