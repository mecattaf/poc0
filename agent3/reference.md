# External References

## Qt WebEngine Documentation
- **URL**: https://doc.qt.io/qt-6/qtwebengine-index.html
- **Action**: ADOPT
- **What**: Official initialization pattern, QML API reference
- **Key pages**:
  - "Deploying Qt WebEngine Applications"
  - "Qt WebEngine Platform Notes" (Wayland section)
  - "WebEngineView QML Type"

## Qt WebEngine Quick Module
- **URL**: https://doc.qt.io/qt-6/qtwebenginequick-module.html
- **Action**: ADOPT
- **What**: `QtWebEngineQuick::initialize()` documentation
- **Critical**: "This function must be called before the QGuiApplication instance is created."

## quickshell-webengine-git Patch
- **URL**: (local: `quickshell-webengine-git/quickshell-webengine-git.patch`)
- **Action**: ADAPT
- **What**: CMake pattern for adding WebEngine to compositor
- **Adopt**:
```cmake
if (WEBENGINE_effective)
    list(APPEND QT_FPDEPS WebEngineQuick WebChannel)
endif()

target_link_libraries(quickshell PRIVATE Qt6::WebEngineQuick Qt6::WebChannel)
target_compile_definitions(quickshell PRIVATE QS_WEBENGINE)
```
- **Adapt**: 
  - Remove conditional (always enable WebEngine)
  - Change target name to `webcompositor`

## quickshell-webengine-git Launch Code
- **URL**: (local: `quickshell-webengine-git/quickshell-webengine-git.patch`)
- **Action**: ADOPT
- **What**: Initialization sequence pattern
```cpp
#ifdef QS_WEBENGINE
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#endif

// ...

#ifdef QS_WEBENGINE
QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
QtWebEngineQuick::initialize();
#endif
```

## Treeland (negative reference)
- **URL**: `external/waylib-shared/src/`
- **Action**: REFERENCE (confirm non-usage)
- **What**: Verify Treeland does NOT use WebEngine
- **Search result**: No QtWebEngine includes found
- **Implication**: We are pioneering this integration

## waylib tinywl QML
- **URL**: `external/waylib-shared/waylib/examples/tinywl/`
- **Action**: ADAPT
- **What**: WOutputRenderWindow usage pattern
- **Study**:
  - `main.cpp` — QmlEngine creation
  - `helper.cpp` — WOutputRenderWindow instantiation
  - `PrimaryOutput.qml` — Output QML structure
- **Adapt**: Replace their QML content with WebEngineView

## Qt Quick and WebEngine Integration
- **URL**: https://doc.qt.io/qt-6/qtwebengine-webengineview-example.html
- **Action**: ADOPT
- **What**: Basic WebEngineView QML pattern
```qml
import QtQuick
import QtWebEngine

Window {
    WebEngineView {
        anchors.fill: parent
        url: "https://www.qt.io"
    }
}
```

## REJECT

### Electron / CEF
- **Action**: REJECT
- **Why**: Different architecture. We use Qt's WebEngine, not standalone Chromium.

### QtWaylandCompositor examples
- **Action**: REJECT  
- **Why**: We use wlroots/waylib, not QtWaylandCompositor.

### Complex WebEngine features
- **Action**: REJECT for Agent 3
- **Features to skip**:
  - WebChannel (Agent 4)
  - Custom URL schemes
  - Download handling
  - Cookie management
  - Certificate handling

## Test Verification Approach

### Standalone WebEngine test (baseline)
```cpp
// If compositor integration fails, test this first:
int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/test-standalone.qml"));
    
    return app.exec();
}
```

### Failure diagnosis
1. Standalone works, compositor fails → GL context conflict
2. Both fail → WebEngine/Wayland issue
3. Compositor works → Success, proceed to Agent 4
