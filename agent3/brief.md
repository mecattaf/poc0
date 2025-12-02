# Agent 3: WebEngine Embed

## Implements
- POC-1: WebEngineView inside QQuickWindow (partial)
- POC-2: WebEngine inside waylib compositor (core)

## Scope
Add QtWebEngine to the waylib compositor scene graph. This agent:
- Adds WebEngine CMake dependencies
- Creates QQuickWindow for compositor output
- Embeds WebEngineView as QML item
- Verifies WebEngine renders without GL context conflicts

No WebChannel yet. No surface composition with WebEngine. Pure rendering test.

## Prerequisites
- Agent 2 deliverables complete
- Working minimal compositor

## Deliverables

### 1. CMake Additions
```cmake
find_package(Qt6 6.10 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    WebEngineQuick
)

target_link_libraries(webcompositor PRIVATE
    Qt6::WebEngineQuick
)

target_compile_definitions(webcompositor PRIVATE
    QT_WEBENGINE_ENABLED
)
```

### 2. Initialization Sequence Update
```cpp
// BEFORE QGuiApplication (CRITICAL)
QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
QtWebEngineQuick::initialize();

// Existing init
qw_log::init();
WRenderHelper::setupRendererBackend();
WServer::initializeQPA();

QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
QGuiApplication app(argc, argv);
```

### 3. QML Scene Structure
```qml
// main.qml
import QtQuick
import QtWebEngine

Item {
    id: root
    anchors.fill: parent

    // Test WebEngine rendering
    WebEngineView {
        id: webView
        anchors.fill: parent
        url: "data:text/html,<h1>WebEngine Working</h1>"
        
        Component.onCompleted: {
            console.log("WebEngineView created")
        }
        
        onLoadingChanged: function(loadRequest) {
            if (loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus) {
                console.log("WebEngine page loaded")
            }
        }
    }
}
```

### 4. WOutputRenderWindow Integration
```cpp
// In Compositor class
WOutputRenderWindow *m_renderWindow;

void Compositor::initRenderWindow() {
    m_renderWindow = new WOutputRenderWindow(this);
    
    // Load QML into render window
    QQmlEngine *engine = m_renderWindow->engine();
    QQmlComponent component(engine, QUrl("qrc:/main.qml"));
    
    QQuickItem *root = qobject_cast<QQuickItem*>(
        component.create(engine->rootContext())
    );
    root->setParentItem(m_renderWindow->contentItem());
}
```

### 5. Output Binding
```cpp
void Compositor::onOutputAdded(WOutput *output) {
    // ... existing output init ...
    
    // Bind output to render window
    m_renderWindow->attach(output);
}
```

### 6. Test HTML
```html
<!-- test.html (embedded as qrc) -->
<!DOCTYPE html>
<html>
<head>
    <style>
        body {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            font-family: system-ui;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
    </style>
</head>
<body>
    <h1>WebCompositor POC</h1>
    <p id="status">WebEngine Rendering OK</p>
</body>
</html>
```

## Success Criteria
- [ ] CMake finds Qt6::WebEngineQuick
- [ ] Compositor starts without GL context errors
- [ ] WebEngineView appears in compositor output
- [ ] WebEngine content renders (gradient visible)
- [ ] No crashes on compositor shutdown
- [ ] Console shows "WebEngine page loaded"

## Constraints
- Do NOT add WebChannel yet (Agent 4)
- Do NOT attempt to render Wayland surfaces (verify only)
- Keep QML under 50 lines
- Use data: URL or embedded qrc for test content

## Known Risk Points
- GL context sharing between wlroots and WebEngine
- QRhi backend compatibility (GLES vs Vulkan)
- WebEngine sandbox permissions on Wayland

## Fallback
If WebEngine fails in compositor context:
1. Log exact error message
2. Test WebEngine in standalone QQuickWindow (no waylib)
3. Report whether issue is waylib-specific or Qt WebEngine on Wayland
