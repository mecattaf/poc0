# Required Reading

## Primary Sources

### Qt WebEngine Initialization
**Critical**: WebEngine initialization MUST happen before QGuiApplication.

```cpp
// From Qt docs - MANDATORY sequence
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

int main(int argc, char *argv[])
{
    // MUST be before QGuiApplication
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngineQuick::initialize();
    
    QGuiApplication app(argc, argv);
    // ...
}
```

### Combined with waylib init
```cpp
// Complete initialization order:

// Phase 1: Qt attributes (before app)
QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

// Phase 2: WebEngine init (before app)  
QtWebEngineQuick::initialize();

// Phase 3: wlroots init
qw_log::init();
WRenderHelper::setupRendererBackend();
WServer::initializeQPA();

// Phase 4: Qt app attributes
QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
    Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
QGuiApplication::setQuitOnLastWindowClosed(false);

// Phase 5: Application
QGuiApplication app(argc, argv);
```

### WOutputRenderWindow
**Location**: `external/waylib-shared/waylib/src/server/qtquick/woutputrenderwindow.h`

Key methods:
```cpp
class WOutputRenderWindow : public QQuickWindow {
    // Get QML content root
    QQuickItem *contentItem();
    
    // Get QML engine
    QQmlEngine *engine();
    
    // Attach output for rendering
    void attach(WOutput *output);
};
```

### QML WebEngineView Properties
```qml
WebEngineView {
    // URL to load
    url: "https://example.com"
    
    // Or inline HTML
    url: "data:text/html,<h1>Hello</h1>"
    
    // Signals
    onLoadingChanged: function(loadRequest) {
        // LoadStartedStatus, LoadStoppedStatus, LoadSucceededStatus, LoadFailedStatus
    }
    
    // WebChannel (for Agent 4)
    webChannel: WebChannel { }
}
```

## CMake Configuration

### Find WebEngine
```cmake
find_package(Qt6 6.10 REQUIRED COMPONENTS
    WebEngineQuick
    WebChannel      # For Agent 4, add now to verify availability
)
```

### Link Libraries
```cmake
target_link_libraries(webcompositor PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::WebEngineQuick
    Waylib::WaylibServer
    QWlroots::QWlroots
)
```

### QML Module
```cmake
qt_add_qml_module(webcompositor
    URI WebCompositor
    VERSION 1.0
    QML_FILES
        qml/main.qml
    RESOURCES
        html/test.html
)
```

## Resource Embedding

### qrc file
```xml
<RCC>
    <qresource prefix="/">
        <file>qml/main.qml</file>
        <file>html/test.html</file>
    </qresource>
</RCC>
```

### Loading from qrc
```qml
WebEngineView {
    url: "qrc:/html/test.html"
}
```

## Debugging WebEngine

### Environment Variables
```bash
# WebEngine debug output
export QTWEBENGINE_CHROMIUM_FLAGS="--enable-logging --v=1"

# Disable GPU sandbox (if permission issues)
export QTWEBENGINE_CHROMIUM_FLAGS="--no-sandbox --disable-gpu-sandbox"

# Force software rendering (fallback)
export QTWEBENGINE_CHROMIUM_FLAGS="--disable-gpu"
```

### Common Errors

#### "Failed to create GBM device"
- WebEngine can't access DRM
- Try: `--disable-gpu-sandbox`

#### "GLPlatformContext: eglCreateContext failed"
- GL context sharing issue
- Verify: `Qt::AA_ShareOpenGLContexts` set before app

#### Black WebEngineView
- Rendering surface not created
- Check: WOutputRenderWindow attached to output

## Architecture Notes

### Why AA_ShareOpenGLContexts
- WebEngine creates its own GL context for Chromium
- Without sharing, WebEngine can't render to Qt's surface
- Must be set before QGuiApplication constructor

### Why initialize() before QGuiApplication
- WebEngine registers platform-specific backends
- These must exist before Qt creates its platform integration
- Order: WebEngine init → waylib QPA init → QGuiApplication

### WOutputRenderWindow vs QQuickWindow
- WOutputRenderWindow IS a QQuickWindow
- Adds wlroots output attachment
- Manages frame callbacks and buffer swapping
- contentItem() is standard QQuickWindow API
