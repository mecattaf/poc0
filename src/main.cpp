#include <QGuiApplication>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <qwlogging.h>
#include <wserver.h>
#include <wrenderhelper.h>

WAYLIB_SERVER_USE_NAMESPACE

#include "compositor.h"

int main(int argc, char *argv[])
{
    // Phase 1: Set Qt attributes BEFORE anything else
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setQuitOnLastWindowClosed(false);

    // Phase 2: Initialize QtWebEngine early (before QGuiApplication)
    // This must happen before any WebEngine QML types are registered
    qInfo() << "Initializing QtWebEngine...";
    QtWebEngineQuick::initialize();

    // Phase 3: Initialize platform integration
    // WServer::initializeQPA() sets up Qt Platform Abstraction for Wayland
    qInfo() << "Initializing wlroots/waylib...";
    qw_log::init();
    WRenderHelper::setupRendererBackend();
    WServer::initializeQPA();

    // Phase 4: Create QGuiApplication AFTER platform is initialized
    qInfo() << "Creating QGuiApplication...";
    QGuiApplication app(argc, argv);

    // Phase 5: Create and start compositor
    qInfo() << "Creating compositor...";
    Compositor compositor;
    if (!compositor.start()) {
        qCritical() << "Failed to start compositor";
        return -1;
    }

    qInfo() << "Entering event loop...";
    return app.exec();
}
