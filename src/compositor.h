#pragma once

#include <wglobal.h>
#include <qwglobal.h>

#include <QObject>
#include <QList>

// Forward declarations
WAYLIB_SERVER_BEGIN_NAMESPACE
class WServer;
class WBackend;
class WSeat;
class WOutput;
class WOutputRenderWindow;
WAYLIB_SERVER_END_NAMESPACE

QW_BEGIN_NAMESPACE
class qw_renderer;
class qw_allocator;
class qw_output_layout;
QW_END_NAMESPACE

WAYLIB_SERVER_USE_NAMESPACE
QW_USE_NAMESPACE

class QQmlEngine;
class QQuickItem;

class Compositor : public QObject {
    Q_OBJECT
public:
    explicit Compositor(QObject *parent = nullptr);
    ~Compositor() override;

    bool start();

private:
    void initRenderWindow();

private slots:
    void onOutputAdded(WOutput *output);
    void onOutputRemoved(WOutput *output);

private:
    // Core Wayland
    WServer *m_server;
    WBackend *m_backend;
    WSeat *m_seat;

    // Rendering
    qw_renderer *m_renderer;
    qw_allocator *m_allocator;

    // Outputs
    qw_output_layout *m_outputLayout;
    QList<WOutput*> m_outputs;

    // QML/WebEngine rendering
    WOutputRenderWindow *m_renderWindow;
    QQmlEngine *m_qmlEngine;
    QQuickItem *m_rootItem;
};
