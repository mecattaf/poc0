# External References

## qwlroots tinywl
- **URL**: `external/waylib-shared/qwlroots/examples/tinywl/main.cpp`
- **Action**: ADOPT (structure), ADAPT (details)
- **What**: Core initialization sequence. This is the canonical minimal compositor.
- **Adopt**:
  - Class structure with `start()` method
  - Signal connections for `outputAdded`
  - Renderer/allocator autocreate pattern
- **Adapt**:
  - Remove View class (no surface handling)
  - Remove keyboard/pointer handling beyond seat creation
  - Remove xdg_shell initialization

## waylib tinywl
- **URL**: `external/waylib-shared/waylib/examples/tinywl/`
- **Action**: REFERENCE ONLY
- **What**: Shows waylib high-level wrappers. Too complex for POC-0.
- **Study**:
  - `main.cpp` lines 19-40 — initialization order
  - `helper.cpp` constructor — WServer/WBackend setup
- **Do NOT copy**: QML integration, Helper singleton, surface containers

## Treeland Initialization
- **URL**: `external/waylib-shared/src/core/treeland.cpp`
- **Action**: REFERENCE ONLY  
- **What**: Production compositor init. Way too complex.
- **Study only**: Lines 263-329 (constructor flow diagram)

## wlroots tinywl (C reference)
- **URL**: https://gitlab.freedesktop.org/wlroots/wlroots/-/blob/master/tinywl/tinywl.c
- **Action**: REFERENCE
- **What**: Original C implementation. Understand what qwlroots wraps.
- **Study**:
  - `server_new_output()` function
  - `main()` initialization order

## Qt Wayland Compositor (alternative approach)
- **URL**: https://doc.qt.io/qt-6/qtwaylandcompositor-index.html
- **Action**: REJECT
- **Why**: Different architecture. We use wlroots via waylib, not QtWaylandCompositor.

## ADOPT Pattern

### Minimal main.cpp from research
```cpp
int main(int argc, char *argv[]) {
    qw_log::init();
    WRenderHelper::setupRendererBackend();
    WServer::initializeQPA();

    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setQuitOnLastWindowClosed(false);
    
    QGuiApplication app(argc, argv);
    
    Compositor compositor;
    if (!compositor.start())
        return -1;
    
    return app.exec();
}
```

### Output handler from research
```cpp
void onNewOutput(wlr_output *output) {
    output->init_render(*allocator, *renderer);
    auto *mode = output->preferred_mode();
    auto l_output = outputLayout->add_auto(*output);
}
```

## REJECT

### WebEngine initialization
- **Action**: REJECT for Agent 2
- **Why**: Agent 3 scope. Keep compositor pure wlroots.

### XDG Shell
- **Action**: REJECT for Agent 2  
- **Why**: No surface handling in POC-0 skeleton.

### Layer Shell
- **Action**: REJECT for Agent 2
- **Why**: Shell surfaces are post-POC-1.
