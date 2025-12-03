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

    // Phase 2: Create QGuiApplication FIRST
    QGuiApplication app(argc, argv);

    // Phase 3: Initialize QtWebEngine AFTER QGuiApplication exists
    QtWebEngineQuick::initialize();

    // Phase 4: Initialize wlroots/waylib AFTER Qt is fully initialized
    qw_log::init();
    WRenderHelper::setupRendererBackend();
    WServer::initializeQPA();

    // Create and start compositor
    Compositor compositor;
    if (!compositor.start()) {
        qCritical() << "Failed to start compositor";
        return -1;
    }

    qInfo() << "Entering event loop...";
    return app.exec();
}
