#include "compositor.h"

#include <QDebug>
#include <QCoreApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlProperty>
#include <QQuickItem>

// waylib headers
#include <wserver.h>
#include <wbackend.h>
#include <woutput.h>
#include <wseat.h>
#include <wrenderhelper.h>
#include <woutputrenderwindow.h>

// qwlroots headers
#include <qwbackend.h>
#include <qwdisplay.h>
#include <qwoutput.h>
#include <qwoutputlayout.h>
#include <qwlogging.h>
#include <render/qwallocator.h>
#include <render/qwrenderer.h>

Compositor::Compositor(QObject *parent)
    : QObject(parent)
    , m_server(nullptr)
    , m_backend(nullptr)
    , m_seat(nullptr)
    , m_renderer(nullptr)
    , m_allocator(nullptr)
    , m_outputLayout(nullptr)
    , m_renderWindow(nullptr)
    , m_qmlEngine(nullptr)
    , m_rootItem(nullptr)
{
    // Create WServer instance
    m_server = new WServer(this);

    // Attach WBackend (autocreate DRM/Wayland/X11)
    m_backend = m_server->attach<WBackend>();
    if (!m_backend) {
        qCritical() << "Failed to create WBackend";
        return;
    }

    // Create qw_renderer and qw_allocator
    m_renderer = qw_renderer::autocreate(*m_backend->handle());
    if (!m_renderer) {
        qCritical() << "Failed to create renderer";
        return;
    }

    m_renderer->init_wl_display(*m_server->handle());

    m_allocator = qw_allocator::autocreate(*m_backend->handle(), *m_renderer);
    if (!m_allocator) {
        qCritical() << "Failed to create allocator";
        return;
    }

    // Create qw_output_layout
    m_outputLayout = new qw_output_layout(*m_server->handle());
    m_outputLayout->setParent(this);
    if (!m_outputLayout) {
        qCritical() << "Failed to create output layout";
        return;
    }

    // Attach WSeat
    m_seat = m_server->attach<WSeat>();
    if (!m_seat) {
        qCritical() << "Failed to create WSeat";
        return;
    }

    // Connect WBackend::outputAdded signal
    connect(m_backend, &WBackend::outputAdded, this, &Compositor::onOutputAdded);
    connect(m_backend, &WBackend::outputRemoved, this, &Compositor::onOutputRemoved);

    // Initialize render window with WebEngine QML
    initRenderWindow();

    qDebug() << "Compositor initialized";
}

Compositor::~Compositor()
{
    // Cleanup will be handled by Qt parent-child relationships
    // and qwlroots object lifecycle management
}

bool Compositor::start()
{
    if (!m_server || !m_backend) {
        qCritical() << "Compositor not properly initialized";
        return false;
    }

    // Start the backend
    if (!m_backend->handle()->start()) {
        qCritical() << "Failed to start backend";
        return false;
    }

    // Start WServer (creates Wayland socket)
    // Start WServer (creates Wayland socket)
    m_server->start();

    // Set WAYLAND_DISPLAY environment variable
    // Set WAYLAND_DISPLAY environment variable
    // const char *socket = m_server->handle()->socket_name();
    // if (socket) {
    //     qputenv("WAYLAND_DISPLAY", socket);
    //     qInfo() << "Wayland compositor started on socket:" << socket;
    // } else {
    //     qWarning() << "No socket name available";
    // }

    return true;
}

void Compositor::initRenderWindow()
{
    qDebug() << "[DEBUG] initRenderWindow: START";

    // Create WOutputRenderWindow
    qDebug() << "[DEBUG] Creating WOutputRenderWindow...";
    m_renderWindow = new WOutputRenderWindow(this);
    if (!m_renderWindow) {
        qCritical() << "Failed to create WOutputRenderWindow";
        return;
    }
    qDebug() << "[DEBUG] WOutputRenderWindow created successfully";

    // Check if contentItem is available
    QQuickItem *contentItem = m_renderWindow->contentItem();
    qDebug() << "[DEBUG] contentItem pointer:" << (void*)contentItem;
    if (!contentItem) {
        qCritical() << "contentItem() returned nullptr - deferring QML initialization";
        // We'll need to initialize QML later when output is added
        return;
    }

    // Create QML engine
    qDebug() << "[DEBUG] Creating QML engine...";
    m_qmlEngine = new QQmlEngine(this);
    if (!m_qmlEngine) {
        qCritical() << "Failed to create QML engine";
        return;
    }
    qDebug() << "[DEBUG] QML engine created successfully";

    // Load QML component
    qDebug() << "[DEBUG] Loading QML component...";
    QQmlComponent component(m_qmlEngine, QUrl("qrc:/qt/qml/WebCompositor/qml/main.qml"));

    if (component.isError()) {
        qCritical() << "QML component errors:";
        for (const auto &error : component.errors()) {
            qCritical() << "  " << error.toString();
        }
        return;
    }
    qDebug() << "[DEBUG] QML component loaded successfully";

    // Create QML object
    qDebug() << "[DEBUG] Creating QML object...";
    QObject *obj = component.create(m_qmlEngine->rootContext());
    if (!obj) {
        qCritical() << "Failed to create QML object";
        return;
    }
    qDebug() << "[DEBUG] QML object created successfully";

    // Cast to QQuickItem
    qDebug() << "[DEBUG] Casting to QQuickItem...";
    m_rootItem = qobject_cast<QQuickItem*>(obj);
    if (!m_rootItem) {
        qCritical() << "QML root object is not a QQuickItem";
        delete obj;
        return;
    }
    qDebug() << "[DEBUG] QQuickItem cast successful";

    // Set parent and size
    qDebug() << "[DEBUG] Setting parent item...";
    m_rootItem->setParentItem(contentItem);
    qDebug() << "[DEBUG] Setting size...";
    m_rootItem->setSize(contentItem->size());

    // Ensure the item fills the window
    qDebug() << "[DEBUG] Setting anchors.fill...";
    QQmlProperty::write(m_rootItem, "anchors.fill", QVariant::fromValue(contentItem));

    qInfo() << "Render window initialized with WebEngine QML";
    qDebug() << "[DEBUG] initRenderWindow: COMPLETE";
}

void Compositor::onOutputAdded(WOutput *output)
{
    if (!output) {
        qWarning() << "Null output in onOutputAdded";
        return;
    }

    qDebug() << "Output added:" << output->name();

    auto *qwOutput = output->handle();
    if (!qwOutput) {
        qWarning() << "Null qw_output handle";
        return;
    }

    // Initialize rendering on output
    qwOutput->init_render(*m_allocator, *m_renderer);

    // Configure preferred mode using wlroots 0.19 API
    wlr_output_mode *mode = qwOutput->preferred_mode();
    if (mode) {
        qw_output_state state;
        state.set_enabled(true);
        state.set_mode(mode);
        qwOutput->commit_state(state);
        qDebug() << "Output mode set:" << mode->width << "x" << mode->height << "@" << mode->refresh / 1000.0 << "Hz";
    } else {
        qWarning() << "No preferred mode available for output";
    }

    // Add to output layout (automatic positioning)
    m_outputLayout->add_auto(*qwOutput);

    // Track output
    m_outputs.append(output);

    // Attach output to render window
    if (m_renderWindow) {
        output->attach(m_renderWindow);
        qDebug() << "Output" << output->name() << "attached to render window";
    }

    qInfo() << "Output" << output->name() << "configured successfully";
}

void Compositor::onOutputRemoved(WOutput *output)
{
    if (!output) {
        return;
    }

    qDebug() << "Output removed:" << output->name();

    // Remove from tracking list
    m_outputs.removeAll(output);
}
