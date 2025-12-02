# Agent 2: Waylib Minimal Compositor

## Implements
- POC-0: Skeleton Compositor (core initialization)

## Scope
Transform the Qt scaffold into a functioning Wayland compositor using qwlroots. This agent implements the minimum viable compositor that can:
- Initialize wlroots backend
- Create Wayland display socket
- Handle output hotplug
- Render empty frames

No surface handling. No input routing. No QML UI.

## Prerequisites
- Agent 1 deliverables complete
- waylib-shared submodule initialized

## Deliverables

### 1. Updated main.cpp
```cpp
#include <QGuiApplication>
#include <qwlog.h>
#include <wserver.h>
#include <wrenderhelper.h>

int main(int argc, char *argv[])
{
    qw_log::init();
    WRenderHelper::setupRendererBackend();
    WServer::initializeQPA();

    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setQuitOnLastWindowClosed(false);

    QGuiApplication app(argc, argv);
    
    // Compositor initialization here
    
    return app.exec();
}
```

### 2. Compositor Class Structure
```cpp
class Compositor : public QObject {
    Q_OBJECT
public:
    explicit Compositor(QObject *parent = nullptr);
    bool start();

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

private slots:
    void onOutputAdded(WOutput *output);
    void onOutputRemoved(WOutput *output);
};
```

### 3. Initialization Sequence
1. Create `WServer` instance
2. Attach `WBackend` (autocreate DRM/Wayland/X11)
3. Create `qw_renderer` and `qw_allocator`
4. Create `qw_output_layout`
5. Attach `WSeat`
6. Connect `WBackend::outputAdded` signal
7. Call `WServer::start()`
8. Set `WAYLAND_DISPLAY` environment variable

### 4. Output Handling
```cpp
void Compositor::onOutputAdded(WOutput *output) {
    auto *qwOutput = output->handle();
    qwOutput->init_render(m_allocator, m_renderer);
    
    auto *mode = qwOutput->preferred_mode();
    if (mode) {
        qw_output_state state;
        state.set_enabled(true);
        state.set_mode(mode);
        qwOutput->commit_state(state);
    }
    
    m_outputLayout->add_auto(qwOutput);
    m_outputs.append(output);
    
    qDebug() << "Output added:" << output->name();
}
```

### 5. Build Verification
```bash
# Build
cmake --build build

# Run nested in existing Wayland session
WAYLAND_DISPLAY=wayland-0 ./build/src/webcompositor

# Verify socket created
ls -la /run/user/$UID/wayland-*

# Run test client
WAYLAND_DISPLAY=wayland-1 weston-terminal
```

## Success Criteria
- [ ] Compositor starts without crash
- [ ] Wayland socket created (`wayland-1` or similar)
- [ ] Output detected and configured
- [ ] `weston-info` shows compositor globals
- [ ] Frame callbacks fire (even if rendering nothing)

## Constraints
- Do NOT implement xdg_shell (no surface handling)
- Do NOT add QML scene graph integration
- Do NOT handle keyboard/pointer input beyond seat creation
- Keep total code under 300 lines
