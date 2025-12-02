# Required Reading

## Primary Sources

### qwlroots tinywl Example
**Location**: `external/waylib-shared/qwlroots/examples/tinywl/main.cpp`

Critical sections:
- Lines 1-50: Header includes and class declaration
- Lines 51-150: Constructor (initialization sequence)
- Lines 151-200: `start()` method (socket creation, backend start)
- Lines 400-450: `onNewOutput()` handler

### Key Initialization Pattern
```cpp
// MUST follow this exact order:

// 1. Before QGuiApplication
qw_log::init();
WRenderHelper::setupRendererBackend();
WServer::initializeQPA();  // CRITICAL: Must be before QGuiApplication

// 2. QGuiApplication setup
QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
QGuiApplication app(argc, argv);

// 3. Compositor objects
WServer *server = new WServer();
WBackend *backend = server->attach<WBackend>();

// 4. Renderer (after backend)
qw_renderer *renderer = qw_renderer::autocreate(*backend->handle());
renderer->init_wl_display(*server->handle());
qw_allocator *allocator = qw_allocator::autocreate(*backend->handle(), *renderer);

// 5. Output layout
qw_output_layout *layout = new qw_output_layout(*server->handle());

// 6. Seat
WSeat *seat = server->attach<WSeat>();

// 7. Start
backend->handle()->start();
```

### qwlroots Headers Required
```cpp
#include <qwbackend.h>
#include <qwdisplay.h>
#include <qwoutput.h>
#include <qwoutputlayout.h>
#include <qwseat.h>
#include <render/qwallocator.h>
#include <render/qwrenderer.h>
#include <qwlogging.h>
```

### waylib Headers Required  
```cpp
#include <wserver.h>
#include <wbackend.h>
#include <woutput.h>
#include <wseat.h>
#include <wrenderhelper.h>
```

## Key Concepts

### WServer vs qw_display
- `WServer` wraps `wl_display` with Qt integration
- Access underlying handle via `server->handle()` which returns `qw_display*`
- `qw_display` has `operator wl_display*()` for C API calls

### WBackend vs qw_backend
- `WBackend` is waylib's high-level backend wrapper
- Emits `outputAdded(WOutput*)` signal
- `WOutput` wraps `qw_output` which wraps `wlr_output`

### Output Initialization
```cpp
void onOutputAdded(WOutput *output) {
    qw_output *qwOut = output->handle();
    wlr_output *wlrOut = qwOut->handle();
    
    // Initialize rendering on output
    qwOut->init_render(m_allocator, m_renderer);
    
    // Configure mode
    wlr_output_mode *mode = wlrOut->preferred_mode;
    qw_output_state state;
    state.set_enabled(true);
    state.set_mode(mode);
    qwOut->commit_state(state);
    
    // Add to layout
    m_outputLayout->add_auto(qwOut);
}
```

### Event Loop Integration
- `WServer::initializeQPA()` installs Qt platform plugin
- Qt's event loop drives wlroots event loop
- No manual `wl_display_run()` needed — use `app.exec()`

## CMake Additions

### Link Libraries
```cmake
target_link_libraries(webcompositor PRIVATE
    Qt6::Core
    Qt6::Gui
    Waylib::WaylibServer
    QWlroots::QWlroots
)
```

### pkg-config Dependencies
```cmake
pkg_check_modules(WLROOTS REQUIRED IMPORTED_TARGET wlroots-0.19)
pkg_check_modules(WAYLAND REQUIRED IMPORTED_TARGET wayland-server)
target_link_libraries(webcompositor PRIVATE
    PkgConfig::WLROOTS
    PkgConfig::WAYLAND
)
```

## Debugging

### Environment Variables
```bash
# Enable wlroots debug output
export WLR_DEBUG=1

# Force specific backend
export WLR_BACKENDS=wayland  # Nested in Wayland
export WLR_BACKENDS=x11      # Nested in X11
export WLR_BACKENDS=drm      # Direct DRM

# Renderer selection
export WLR_RENDERER=gles2
export WLR_RENDERER=vulkan
```

### Verification Commands
```bash
# Check socket
WAYLAND_DISPLAY=wayland-1 weston-info

# Should show:
# interface: 'wl_compositor', version: 6
# interface: 'wl_subcompositor', version: 1
# interface: 'wl_seat', version: 9
```
