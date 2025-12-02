
ib-shared/docs/research.md
# waylib-shared Research Documentation for POC 0 (Skeleton Compositor)

 

## Overview

 

waylib-shared is a comprehensive Qt-based Wayland compositor framework that provides a high-level abstraction over wlroots. It consists of three main components that work together to enable rapid Wayland compositor development.

 

**Project Version:** 0.7.0

**Last Updated:** 2025-12-02

 

---

 

## Repository Structure

 

### 1. Core Components

 

#### qwlroots (Qt wrapper for wlroots)

- **Location:** `qwlroots/`

- **Version:** 0.5.3

- **Purpose:** Low-level Qt wrapper around wlroots C library

- **Language:** C++ (C++20)

- **Build System:** CMake 3.21+

 

#### waylib (High-level compositor framework)

- **Location:** `waylib/`

- **Version:** 0.6.13

- **Purpose:** Higher-level Qt/QML framework for building compositors

- **Language:** C++ (C++20) with QML support

- **Build System:** CMake 3.21+

 

#### treeland (Full compositor implementation)

- **Location:** Root directory

- **Version:** 0.7.0 (QuickWaylibServer)

- **Purpose:** Complete compositor implementation using waylib

- **Note:** Most files are in `src-unused/` indicating modular development

 

### 2. Examples Directory Structure

 

The repository contains two sets of example compositors:

 

#### qwlroots/examples/tinywl/

Minimal compositor using only qwlroots (C++ only, no QML).

 

#### waylib/examples/tinywl/

Advanced compositor using waylib with full QML support:

- **Main files:**

  - `main.cpp` - Application entry point

  - `helper.h/cpp` - Core compositor logic

  - `workspace.h/cpp` - Workspace management

  - `output.h/cpp` - Output management

  - `qmlengine.h/cpp` - QML engine integration

  - `surfacecontainer.h/cpp` - Surface container management

  - `layersurfacecontainer.h/cpp` - Layer surface handling

  - `rootsurfacecontainer.h/cpp` - Root surface container

  - `surfaceproxy.h/cpp` - Surface proxy abstraction

  - `surfacewrapper.h/cpp` - Surface wrapper utilities

  - `wallpaperimage.h/cpp` - Wallpaper support

  - `wallpaperprovider.h/cpp` - Wallpaper provider

  - `workspacemodel.h/cpp` - Workspace model

 

- **QML files:**

  - `PrimaryOutput.qml` - Primary output setup

  - `CopyOutput.qml` - Output copying

  - `TitleBar.qml` - Window title bar

  - `Decoration.qml` - Window decorations

  - `TaskBar.qml` - Task bar

  - `SurfaceContent.qml` - Surface rendering

  - `Shadow.qml` - Shadow effects

  - `Border.qml` - Window borders

  - `GeometryAnimation.qml` - Geometry animations

  - `OutputMenuBar.qml` - Output menu

  - `WorkspaceSwitcher.qml` - Workspace switching

  - `WorkspaceProxy.qml` - Workspace proxy

  - `WindowMenu.qml` - Window menu

 

#### waylib/examples/ (Additional examples)

- `animationclient/` - Client animation demo

- `blur/` - Blur effects demo

- `outputcopy/` - Output copying demo

- `outputviewport/` - Output viewport demo

- `surface-delegate/` - Surface delegate example

 

### 3. Test Examples

 

The `examples/` directory contains extensive test clients:

- `test_capture/` - Screen capture testing

- `test_data_control_manager/` - Data control manager

- `test_hide_window/` - Window hiding

- `test_monitor_active_event/` - Monitor events

- `test_multitaskview/` - Multi-task view

- `test_pinch_handler/` - Pinch gesture handling

- `test_primary_output/` - Primary output management

- `test_set_treeland_wallpaper/` - Wallpaper setting

- `test_show_desktop/` - Show desktop functionality

- `test_super_overlay_surface/` - Overlay surfaces

- `test_virtual_output/` - Virtual output creation

- `test_wallpaper_color/` - Wallpaper color extraction

- `test_window_appearance/` - Window appearance customization

- `test_window_bg/` - Window backgrounds

- `test_window_cursor/` - Window cursor management

- `test_window_overlapped/` - Window overlap handling

- `test_window_picker/` - Window picker

- `test_xdgport_wallpaper/` - XDG portal wallpaper

 

---

 

## Dependencies

 

### Required Qt6 Modules

 

#### Core Qt Modules (from root CMakeLists.txt)

```cmake

Qt6::Core

Qt6::DBus

Qt6::Gui

Qt6::Qml

Qt6::Quick

Qt6::QuickControls2

Qt6::LinguistTools

Qt6::Test

Qt6::QuickTest

```

 

**Minimum Qt Version:** 6.8+ (as specified by `qt_standard_project_setup(REQUIRES 6.8)`)

 

#### Private Qt Modules (from waylib/src/server/CMakeLists.txt)

```cmake

Qt6::GuiPrivate

Qt6::QuickPrivate

```

 

### System Dependencies

 

#### Core Libraries (via pkg-config)

```

wlroots-0.19       # Wayland compositor library

wayland-server     # Wayland server library

wayland-protocols  # Standard Wayland protocols

wlr-protocols      # wlroots-specific protocols

pixman-1           # Low-level pixel manipulation

xkbcommon          # Keyboard handling

libdrm             # Direct Rendering Manager

xcb                # X11 protocol C bindings

egl                # OpenGL ES/EGL

```

 

#### Build Tools

```

CMake 3.25.0+      # Build system

PkgConfig          # Dependency discovery

C++20 compiler     # GCC/Clang with C++20 support

```

 

### Optional Dependencies

- **XWayland support:** Can be disabled with `-DDISABLE_XWAYLAND=ON`

- **ECM (Extra CMake Modules):** Optional for enhanced CMake support (KDE)

- **Address Sanitizer:** Optional for debugging (`-DADDRESS_SANITIZER=ON`)

 

---

 

## CMakeLists.txt Analysis

 

### Root CMakeLists.txt Structure

 

```cmake

project(QuickWaylibServer VERSION 0.7.0)

 

# Key Options

option(WITH_SUBMODULE_WAYLIB "Use waylib from git submodule" ON)

option(ADDRESS_SANITIZER "Enable address sanitizer" OFF)

option(BUILD_TREELAND_EXAMPLES "Build clients demo" OFF)

option(DISABLE_DDM "Disable DDM and greeter" ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

 

# Build Configuration

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

 

# Submodule Integration

if(WITH_SUBMODULE_WAYLIB)

  set(WITH_SUBMODULE_QWLROOTS ON)

  set(BUILD_SHARED_LIBS_WAYLIB ${BUILD_SHARED_LIBS})

  set(BUILD_SHARED_QWLROOTS_LIBS OFF)  # Always static

  add_subdirectory(waylib)

endif()

```

 

**Key Features:**

- Enforces C++20 standard

- Supports submodule-based or system-installed waylib

- qwlroots is always built as static library

- Optional features: DDM (Display/Greeter Manager), Address Sanitizer

- Qt logging context enabled by default (`QT_MESSAGELOGCONTEXT`)

- Force asserts enabled for development (`QT_FORCE_ASSERTS`)

 

### waylib/CMakeLists.txt Structure

 

```cmake

project(Waylib VERSION 0.6.13)

 

# Key Options

option(WITH_SUBMODULE_QWLROOTS "Use QWlroots from submodule" ON)

option(BUILD_WAYLIB_EXAMPLES "Build MVP compositor examples" ON)

option(BUILD_WAYLIB_TESTS "Build test demos" ON)

option(DISABLE_XWAYLAND "Disable xwayland support" OFF)

option(INSTALL_TINYWL "Install tinywl compositor" OFF)

option(ADDRESS_SANITIZER "Enable address sanitize" OFF)

option(WAYLIB_USE_PERCOMPILE_HEADERS "Use precompile headers" OFF)

 

# Submodule Integration

if(WITH_SUBMODULE_QWLROOTS)

  set(BUILD_SHARED_QWLROOTS_LIBS OFF)  # Always static

  add_subdirectory(../qwlroots qwlroots)

endif()

```

 

### qwlroots/CMakeLists.txt Structure

 

```cmake

project(QWlroots VERSION 0.5.3)

 

# Key Options

option(PREFER_QT_5 "Prefer Qt 5 over Qt 6" OFF)

option(USE_WLROOTS_19 "Use wlroots 0.19 version" ON)

option(QWLROOTS_USE_PERCOMPILE_HEADERS "Use precompile headers" OFF)

option(DISABLE_WLR_PROTOCOLS "Disable wlr protocols" OFF)

option(DISABLE_XWAYLAND "Disable xwayland support" OFF)

option(BUILD_SHARED_QWLROOTS_LIBS "Build shared libraries" OFF)

option(BUILD_QWLROOTS_EXAMPLES "Build examples" ON)

option(BUILD_QWLROOTS_TESTS "Build tests" ON)

 

# Wayland Protocol Generation

ws_generate(server wayland-protocols stable/xdg-shell/xdg-shell.xml ...)

ws_generate(server wayland-protocols unstable/fullscreen-shell/...)

# ... additional protocol generation

```

 

---

 

## Minimal Compositor Examples

 

### 1. qwlroots/examples/tinywl (C++ Only - 685 lines)

 

**File:** `qwlroots/examples/tinywl/main.cpp`

 

This is the most minimal viable Wayland compositor example, similar to wlroots' original tinywl.

 

#### Core Structure

 

```cpp

class TinywlServer : public QObject {

public:

    TinywlServer();

    bool start();

 

private:

    // Core Wayland objects

    qw_display *display;

    qw_backend *backend;

    qw_renderer *renderer;

    qw_allocator *allocator;

 

    // Wayland protocols

    qw_compositor *compositor;

    qw_subcompositor *subcompositor;

    qw_data_device_manager *dataDeviceManager;

 

    // Output management

    qw_output_layout *outputLayout;

    QList<qw_output*> outputs;

 

    // Scene graph

    qw_scene *scene;

    qw_scene_output_layout *scene_layout;

 

    // Shell protocol

    qw_xdg_shell *xdgShell;

    QList<View*> views;

 

    // Input handling

    qw_cursor *cursor;

    qw_xcursor_manager *cursorManager;

    QList<qw_keyboard*> keyboards;

    qw_seat *seat;

};

```

 

#### Initialization Sequence

 

```cpp

TinywlServer::TinywlServer() {

    // 1. Create display

    display = new qw_display();

 

    // 2. Create backend (auto-detect: DRM, X11, Wayland, etc.)

    backend = qw_backend::autocreate(display->get_event_loop(), nullptr);

 

    // 3. Create renderer (auto-detect: GLES2, Vulkan, etc.)

    renderer = qw_renderer::autocreate(*backend);

    renderer->init_wl_display(*display);

 

    // 4. Create allocator

    allocator = qw_allocator::autocreate(*backend, *renderer);

 

    // 5. Initialize core protocols

    compositor = qw_compositor::create(*display, 4, *renderer);

    subcompositor = qw_subcompositor::create(*display);

    dataDeviceManager = qw_data_device_manager::create(*display);

 

    // 6. Setup output layout

    outputLayout = new qw_output_layout(*display);

 

    // 7. Create scene graph

    scene = qw_scene::create();

    scene_layout = qw_scene_output_layout::from(

        scene->attach_output_layout(*outputLayout));

 

    // 8. Initialize XDG shell

    xdgShell = qw_xdg_shell::create(*display, 3);

 

    // 9. Setup cursor

    cursor = qw_cursor::create();

    cursor->attach_output_layout(*outputLayout);

    cursorManager = qw_xcursor_manager::create(nullptr, 24);

 

    // 10. Create seat

    seat = qw_seat::create(*display, "seat0");

 

    // Connect signals...

}

 

bool TinywlServer::start() {

    // Create Wayland socket

    const char *socket = display->add_socket_auto();

 

    // Start backend

    if (!backend->start())

        return false;

 

    // Set environment variable

    qputenv("WAYLAND_DISPLAY", QByteArray(socket));

 

    // Start event loop

    display->start(qApp->thread());

    return true;

}

 

int main(int argc, char **argv) {

    qw_log::init();

    QGuiApplication app(argc, argv);

 

    TinywlServer server;

    if (!server.start())

        return -1;

 

    return app.exec();

}

```

 

#### Key Event Handlers

 

```cpp

// Output handling

void onNewOutput(wlr_output *output) {

    // Initialize output rendering

    output->init_render(*allocator, *renderer);

 

    // Set preferred mode

    auto *mode = output->preferred_mode();

 

    // Add to output layout

    auto l_output = outputLayout->add_auto(*output);

 

    // Attach to scene

    auto sceneOutput = qw_scene_output::create(*scene, *output);

    scene_layout->add_output(l_output, *sceneOutput);

}

 

// Surface handling

void onNewXdgToplevel(wlr_xdg_toplevel *toplevel) {

    auto view = new View();

    view->xdgToplevel = qw_xdg_toplevel::from(toplevel);

    view->sceneTree = qw_scene::xdg_surface_create(&(*scene)->tree, toplevel->base);

 

    // Connect signals for map/unmap, move, resize, etc.

}

 

// Input handling

void onCursorMotion(wlr_pointer_motion_event *event) {

    cursor->move(&event->pointer->base, event->delta_x, event->delta_y);

    processCursorMotion(event->time_msec);

}

 

void onKeyboardKey(wlr_keyboard_key_event *event) {

    // Handle keybindings (Ctrl+Alt+Escape to quit, etc.)

    // Forward to focused surface

    seat->keyboard_notify_key(event->time_msec,

                               event->keycode,

                               event->state);

}

```

 

#### CMakeLists.txt

 

```cmake

project(tinywl)

 

find_package(QWlroots REQUIRED)

find_package(Qt6 COMPONENTS Gui REQUIRED)

 

add_executable(tinywl main.cpp)

 

target_link_libraries(tinywl

    PRIVATE

    QWlroots::QWlroots

    Qt6::Gui

)

```

 

**Total Dependencies:** 2 libraries (QWlroots, Qt6::Gui)

 

---

 

### 2. waylib/examples/tinywl (Qt/QML - Advanced)

 

**Main File:** `waylib/examples/tinywl/main.cpp` (55 lines)

 

This example demonstrates a full-featured compositor using waylib's high-level abstractions and QML for UI.

 

#### Main Entry Point

 

```cpp

int main(int argc, char *argv[]) {

    // Initialize logging

    qw_log::init();

 

    // Setup renderer backend (GLES2, Vulkan, etc.)

    WRenderHelper::setupRendererBackend();

 

    // Initialize QPA (Qt Platform Abstraction)

    WServer::initializeQPA();

 

    // Create Qt application

    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);

    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(

        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QGuiApplication::setQuitOnLastWindowClosed(false);

    QGuiApplication app(argc, argv);

 

    // Create QML engine

    QmlEngine *qmlEngine = new QmlEngine;

 

    // Get singleton Helper instance

    Helper *helper = qmlEngine->singletonInstance<Helper*>("Tinywl", "Helper");

    helper->init();

 

    return app.exec();

}

```

 

#### Helper Class Structure

 

**File:** `waylib/examples/tinywl/helper.h`

 

```cpp

class Helper : public WSeatEventFilter {

    Q_OBJECT

    Q_PROPERTY(bool socketEnabled ...)

    Q_PROPERTY(SurfaceWrapper* activatedSurface ...)

    Q_PROPERTY(RootSurfaceContainer* rootContainer ...)

    Q_PROPERTY(Workspace* workspace ...)

    QML_ELEMENT

    QML_SINGLETON

 

public:

    explicit Helper(QObject *parent = nullptr);

    void init();

 

private:

    // Qt/QML infrastructure

    WOutputRenderWindow *m_renderWindow;

    QObject *m_windowMenu;

 

    // Wayland core objects

    WServer *m_server;

    WSocket *m_socket;

    WSeat *m_seat;

    WBackend *m_backend;

    qw_renderer *m_renderer;

    qw_allocator *m_allocator;

 

    // Wayland protocols

    qw_compositor *m_compositor;

    WXWayland *m_xwayland;

    WInputMethodHelper *m_inputMethodHelper;

    WXdgDecorationManager *m_xdgDecorationManager;

    WForeignToplevel *m_foreignToplevel;

    WExtForeignToplevelListV1 *m_extForeignToplevelListV1;

 

    // Compositor-specific

    QList<Output*> m_outputList;

    RootSurfaceContainer *m_surfaceContainer;

    LayerSurfaceContainer *m_backgroundContainer;

    LayerSurfaceContainer *m_bottomContainer;

    Workspace *m_workspace;

    LayerSurfaceContainer *m_topContainer;

    LayerSurfaceContainer *m_overlayContainer;

    SurfaceContainer *m_popupContainer;

    SurfaceContainer *m_lockContainer;

    WSessionLock *m_sessionLock;

};

```

 

#### Key Features

 

1. **QML Integration:** Full QML support for compositor UI

2. **High-level Abstractions:**

   - `WServer` - Server management

   - `WSocket` - Socket handling

   - `WSeat` - Seat management

   - `WOutputRenderWindow` - Output rendering

   - `WBackend` - Backend abstraction

3. **Protocol Support:**

   - XWayland integration

   - Input method (IME) support

   - XDG decorations

   - Foreign toplevel management

   - Session lock

4. **Surface Management:**

   - Layer surface containers (background, bottom, top, overlay)

   - Root surface container

   - Popup container

   - Lock screen container

5. **Workspace Support:** Multi-workspace functionality

6. **Advanced Features:**

   - Window animations

   - Blur effects

   - Shadow effects

   - Custom decorations

   - Task bar

   - Window menu

 

#### CMakeLists.txt

 

```cmake

find_package(Qt6 COMPONENTS Quick QuickControls2 REQUIRED)

find_package(Qt6 COMPONENTS QuickPrivate QUIET)

qt_standard_project_setup(REQUIRES 6.8)

 

find_package(PkgConfig REQUIRED)

pkg_search_module(PIXMAN REQUIRED IMPORTED_TARGET pixman-1)

pkg_search_module(WAYLAND REQUIRED IMPORTED_TARGET wayland-server)

 

set(TARGET tinywl-qtquick)

 

add_executable(${TARGET} main.cpp)

 

qt_add_qml_module(${TARGET}

    URI Tinywl

    VERSION "2.0"

    SOURCES helper.h helper.cpp

    SOURCES surfacewrapper.h surfacewrapper.cpp

    SOURCES workspace.h workspace.cpp

    SOURCES output.h output.cpp

    # ... additional C++ sources

    QML_FILES PrimaryOutput.qml

    QML_FILES CopyOutput.qml

    QML_FILES TitleBar.qml

    # ... additional QML files

)

 

target_link_libraries(${TARGET}

    PRIVATE

    Qt6::Quick

    Qt6::QuickControls2

    Qt6::QuickPrivate

    Waylib::SharedServer

    PkgConfig::PIXMAN

    PkgConfig::WAYLAND

)

```

 

**Total Dependencies:** 6 libraries (Qt6::Quick, Qt6::QuickControls2, Qt6::QuickPrivate, Waylib::SharedServer, pixman-1, wayland-server)

 

---

 

## Protocol Support

 

### waylib Server Implementation

 

**Location:** `waylib/src/server/protocols/`

 

Implemented protocols include:

 

#### Core Protocols

- **XDG Shell:** Window management (`wxdgshell.*`, `wxdgsurface.*`, `wxdgtoplevelsurface.*`, `wxdgpopupsurface.*`)

- **XDG Output:** Output information (`wxdgoutput.*`)

- **XDG Decoration:** Server-side decorations (`wxdgdecorationmanager.*`)

- **Layer Shell:** Layer surfaces for panels/backgrounds (`wlayershell.*`, `wlayersurface.*`)

 

#### XWayland Support

- **XWayland:** X11 application support (`wxwayland.*`, `wxwaylandsurface.*`)

- Can be disabled with `-DDISABLE_XWAYLAND=ON`

 

#### Input Protocols

- **Input Method:** IME support (`winputmethodhelper.*`, `winputpopupsurface.*`)

- **Text Input v1/v2/v3:** Various text input protocols (in `private/`)

- **Virtual Keyboard v1:** Virtual keyboard support (in `private/`)

- **Cursor Shape v1:** Cursor shape management (`wcursorshapemanagerv1.*`)

 

#### Window Management

- **Foreign Toplevel v1:** Window list for panels (`wforeigntoplevelv1.*`)

- **Ext Foreign Toplevel List v1:** Extended toplevel list (`wextforeigntoplevellistv1.*`)

- **Output Manager v1:** Output configuration (`woutputmanagerv1.*`)

 

#### Security & Session

- **Security Context Manager:** Security context isolation (`wsecuritycontextmanager.*`)

- **Session Lock:** Lock screen protocol (`wsessionlockmanager.*`, `wsessionlock.*`, `wsessionlocksurface.*`)

 

#### Advanced Features

- **Ext Image Capture Source v1:** Screen capture source management (`wextimagecapturesourcev1impl.*`)

 

### Wayland Protocol Generation

 

The build system uses the `ws_generate()` CMake function to generate protocol bindings from XML files:

 

```cmake

ws_generate(server wayland-protocols

    stable/xdg-shell/xdg-shell.xml

    xdg-shell-protocol)

 

ws_generate(server wayland-protocols

    staging/color-management/color-management-v1.xml

    color-management-v1-protocol)

 

ws_generate(server wlr-protocols

    unstable/wlr-layer-shell-unstable-v1.xml

    wlr-layer-shell-unstable-v1-protocol)

```

 

---

 

## Waylib Architecture

 

### Layer Architecture

 

```

┌─────────────────────────────────────────┐

│         Application / Compositor        │

│         (treeland, tinywl, etc.)        │

└─────────────────────────────────────────┘

                    ↓

┌─────────────────────────────────────────┐

│            Waylib QtQuick               │

│     (QML Components, Surface Items)     │

└─────────────────────────────────────────┘

                    ↓

┌─────────────────────────────────────────┐

│          Waylib Server Kernel           │

│   (WServer, WSeat, WOutput, WSurface)   │

└─────────────────────────────────────────┘

                    ↓

┌─────────────────────────────────────────┐

│          Waylib Protocols               │

│    (XDG Shell, Layer Shell, XWayland)   │

└─────────────────────────────────────────┘

                    ↓

┌─────────────────────────────────────────┐

│             QWlroots                    │

│      (Qt Wrapper for wlroots)           │

└─────────────────────────────────────────┘

                    ↓

┌─────────────────────────────────────────┐

│             wlroots 0.19                │

│     (C library for Wayland compositors) │

└─────────────────────────────────────────┘

```

 

### Key Directories

 

#### waylib/src/server/kernel/

Core compositor infrastructure:

- `wserver.*` - Server initialization and management

- `wbackend.*` - Backend abstraction (DRM, X11, Wayland, Headless)

- `woutput.*` - Output management

- `wseat.*` - Seat (input) management

- `wcursor.*` - Cursor handling

- `wsurface.*` - Surface abstraction

- `wtoplevelsurface.*` - Toplevel surface base class

- `winputdevice.*` - Input device handling

- `woutputlayout.*` - Output layout management

- `wevent.*` - Event handling

- `wtypes.*` - Common types

- `wsocket.*` - Socket management

 

#### waylib/src/server/qtquick/

Qt Quick/QML integration:

- `wsurfaceitem.*` - QML item for rendering surfaces

- `woutputitem.*` - QML item for outputs

- `woutputviewport.*` - Output viewport management

- `woutputlayer.*` - Output layer compositing

- `woutputrenderwindow.*` - Main render window

- `wxdgtoplevelsurfaceitem.*` - XDG toplevel surface item

- `wxdgpopupsurfaceitem.*` - XDG popup surface item

- `wlayersurfaceitem.*` - Layer surface item

- `wxwaylandsurfaceitem.*` - XWayland surface item

- `winputpopupsurfaceitem.*` - Input popup surface item

- `wrenderhelper.*` - Rendering utilities

- `wqmlcreator.*` - QML object creation helper

 

#### waylib/src/server/utils/

Utility classes:

- `wtools.*` - General utilities

- `wthreadutils.*` - Threading utilities

- `wcursorimage.*` - Cursor image handling

- `wimagebuffer.*` - Image buffer management

- `wbufferdumper.*` - Buffer dumping for debugging

- `wwrappointer.*` - Smart pointer wrapper

 

#### waylib/src/server/platformplugin/

Qt Platform Abstraction (QPA) integration:

- `qwlrootsintegration.*` - Main QPA plugin

- `qwlrootscreen.*` - Screen implementation

- `qwlrootswindow.*` - Window implementation

- `qwlrootscursor.*` - Cursor implementation

 

---

 

## Building a Minimal Compositor

 

### Option 1: Using qwlroots Only (C++ Only)

 

**Pros:**

- Minimal dependencies (just Qt6::Gui and QWlroots)

- Full control over compositor behavior

- Closer to wlroots C API

- Smaller binary size

 

**Cons:**

- More boilerplate code

- No QML support

- Need to implement more features manually

 

**Steps:**

1. Link against `QWlroots::QWlroots` and `Qt6::Gui`

2. Create `qw_display`, `qw_backend`, `qw_renderer`, `qw_allocator`

3. Initialize protocols: `qw_compositor`, `qw_xdg_shell`, `qw_seat`

4. Setup scene graph: `qw_scene`, `qw_scene_output_layout`

5. Handle events via Qt signals/slots

6. Implement input handling and surface management

 

**Reference:** `qwlroots/examples/tinywl/main.cpp`

 

### Option 2: Using waylib (Qt/QML)

 

**Pros:**

- High-level abstractions reduce code

- Full QML support for compositor UI

- Rich protocol support out of the box

- Advanced features (animations, effects, workspaces)

- Better suited for production compositors

 

**Cons:**

- More dependencies

- Larger binary size

- More complex build setup

- Steeper learning curve for architecture

 

**Steps:**

1. Link against `Waylib::SharedServer`, Qt Quick modules

2. Initialize with `WRenderHelper::setupRendererBackend()` and `WServer::initializeQPA()`

3. Create `QmlEngine` and load QML UI

4. Get `Helper` singleton and call `init()`

5. Implement compositor logic in C++ helper classes

6. Design UI in QML files

 

**Reference:** `waylib/examples/tinywl/`

 

---

 

## Build Configuration

 

### Building from Submodules (Default)

 

```bash

cmake -B build \

    -DCMAKE_BUILD_TYPE=Release \

    -DWITH_SUBMODULE_WAYLIB=ON \

    -DWITH_SUBMODULE_QWLROOTS=ON \

    -DBUILD_TREELAND_EXAMPLES=ON \

    -DBUILD_WAYLIB_EXAMPLES=ON \

    -DBUILD_QWLROOTS_EXAMPLES=ON

 

cmake --build build -j$(nproc)

```

 

### Building with System Libraries

 

```bash

cmake -B build \

    -DCMAKE_BUILD_TYPE=Release \

    -DWITH_SUBMODULE_WAYLIB=OFF \

    -DCMAKE_PREFIX_PATH="/usr/lib/cmake/Waylib;/usr/lib/cmake/QWlroots"

 

cmake --build build -j$(nproc)

```

 

### Building Specific Components

 

```bash

# Build only qwlroots

cd qwlroots

cmake -B build -DBUILD_QWLROOTS_EXAMPLES=ON

cmake --build build -j$(nproc)

 

# Build only waylib

cd waylib

cmake -B build -DWITH_SUBMODULE_QWLROOTS=ON -DBUILD_WAYLIB_EXAMPLES=ON

cmake --build build -j$(nproc)

```

 

### Install Targets

 

```bash

# Install qwlroots

cd qwlroots/build

sudo cmake --install .

 

# Install waylib

cd waylib/build

sudo cmake --install .

 

# Install waylib-shared (treeland)

cd build

sudo cmake --install .

```

 

**Install Locations:**

- Libraries: `/usr/lib/` or `/usr/local/lib/`

- Headers: `/usr/include/qwlroots/` and `/usr/include/waylib/`

- CMake configs: `/usr/lib/cmake/QWlroots/` and `/usr/lib/cmake/Waylib/`

- QML modules: `/usr/lib/qt6/qml/Waylib/QuickSharedServer/`

 

---

 

## POC 0 Recommendations

 

### Recommended Approach: qwlroots tinywl

 

For POC 0 (Skeleton Compositor), I recommend starting with the **qwlroots tinywl example** because:

 

1. **Simplicity:** Single 685-line C++ file demonstrates all core concepts

2. **Minimal Dependencies:** Only requires Qt6::Gui and QWlroots

3. **Clear Structure:** Easy to understand initialization sequence

4. **Well-Documented:** Comments explain each step

5. **Qt Integration:** Uses Qt signals/slots for event handling

6. **Production Ready:** Based on wlroots' reference tinywl implementation

 

### Key Files to Study

 

1. **Main Example:**

   - `qwlroots/examples/tinywl/main.cpp` - Complete minimal compositor

   - `qwlroots/examples/tinywl/CMakeLists.txt` - Build configuration

 

2. **Build System:**

   - `qwlroots/CMakeLists.txt` - qwlroots build configuration

   - `qwlroots/cmake/WaylandScannerHelpers.cmake` - Protocol generation

 

3. **Headers to Include:**

   - `qwlroots/qwbackend.h` - Backend management

   - `qwlroots/qwdisplay.h` - Display/server

   - `qwlroots/qwrenderer.h` - Rendering

   - `qwlroots/render/qwallocator.h` - Buffer allocation

   - `qwlroots/types/qwcompositor.h` - Compositor protocol

   - `qwlroots/types/qwxdgshell.h` - XDG shell protocol

   - `qwlroots/types/qwseat.h` - Seat/input management

   - `qwlroots/types/qwcursor.h` - Cursor handling

   - `qwlroots/types/qwscene.h` - Scene graph

   - `qwlroots/types/qwoutput.h` - Output management

   - `qwlroots/types/qwoutputlayout.h` - Output layout

 

### Initialization Checklist for POC 0

 

```cpp

// 1. Setup Qt application

QGuiApplication app(argc, argv);

qw_log::init();

 

// 2. Create Wayland display

qw_display *display = new qw_display();

 

// 3. Create and start backend

qw_backend *backend = qw_backend::autocreate(display->get_event_loop(), nullptr);

 

// 4. Create renderer

qw_renderer *renderer = qw_renderer::autocreate(*backend);

renderer->init_wl_display(*display);

 

// 5. Create allocator

qw_allocator *allocator = qw_allocator::autocreate(*backend, *renderer);

 

// 6. Initialize core protocols

qw_compositor *compositor = qw_compositor::create(*display, 4, *renderer);

qw_subcompositor *subcompositor = qw_subcompositor::create(*display);

qw_data_device_manager *dataDeviceManager = qw_data_device_manager::create(*display);

 

// 7. Setup output layout

qw_output_layout *outputLayout = new qw_output_layout(*display);

 

// 8. Create scene graph

qw_scene *scene = qw_scene::create();

qw_scene_output_layout *scene_layout = qw_scene_output_layout::from(

    scene->attach_output_layout(*outputLayout));

 

// 9. Initialize XDG shell

qw_xdg_shell *xdgShell = qw_xdg_shell::create(*display, 3);

 

// 10. Setup cursor

qw_cursor *cursor = qw_cursor::create();

cursor->attach_output_layout(*outputLayout);

qw_xcursor_manager *cursorManager = qw_xcursor_manager::create(nullptr, 24);

cursorManager->load(1);

 

// 11. Create seat

qw_seat *seat = qw_seat::create(*display, "seat0");

 

// 12. Connect signals for event handling

connect(backend, &qw_backend::notify_new_output, this, &Server::onNewOutput);

connect(xdgShell, &qw_xdg_shell::notify_new_toplevel, this, &Server::onNewXdgToplevel);

connect(backend, &qw_backend::notify_new_input, this, &Server::onNewInput);

// ... additional signal connections

 

// 13. Create Wayland socket and start

const char *socket = display->add_socket_auto();

backend->start();

qputenv("WAYLAND_DISPLAY", QByteArray(socket));

display->start(qApp->thread());

 

// 14. Run Qt event loop

return app.exec();

```

 

### Essential Event Handlers

 

```cpp

// Output management

void onNewOutput(wlr_output *output);

void onOutputFrame();

 

// Surface management

void onNewXdgToplevel(wlr_xdg_toplevel *toplevel);

void onNewXdgPopup(wlr_xdg_popup *popup);

void onMap();

void onUnmap();

 

// Input management

void onNewInput(wlr_input_device *device);

void onCursorMotion(wlr_pointer_motion_event *event);

void onCursorButton(wlr_pointer_button_event *event);

void onKeyboardKey(wlr_keyboard_key_event *event);

void onKeyboardModifiers();

 

// Request handling

void onXdgToplevelRequestMove(wlr_xdg_toplevel_move_event *event);

void onXdgToplevelRequestResize(wlr_xdg_toplevel_resize_event *event);

void onRequestSetCursor(wlr_seat_pointer_request_set_cursor_event *event);

void onRequestSetSelection(wlr_seat_request_set_selection_event *event);

```

 

---

 

## Testing & Validation

 

### Running the Compositor

 

```bash

# From qwlroots build

./examples/tinywl/tinywl -s weston-terminal

 

# From waylib build

./examples/tinywl/tinywl-qtquick

 

# From nested X11 session (for testing)

DISPLAY=:0 ./tinywl

```

 

### Test Clients

 

The repository includes numerous test clients in `examples/` for validating compositor functionality:

 

```bash

# Test basic functionality

./examples/test_hide_window/test_hide_window

./examples/test_show_desktop/test_show_desktop

 

# Test output management

./examples/test_primary_output/test_primary_output

./examples/test_virtual_output/test_virtual_output

 

# Test window management

./examples/test_window_appearance/test_window_appearance

./examples/test_window_overlapped/test_window_overlapped

 

# Test input handling

./examples/test_pinch_handler/test_pinch_handler

./examples/test_window_cursor/test_window_cursor

 

# Test advanced features

./examples/test_capture/test_capture

./examples/test_multitaskview/test_multitaskview

```

 

### Environment Variables

 

```bash

# Enable wlroots debug logging

export WLR_DEBUG=1

 

# Use software rendering (for testing without GPU)

export WLR_RENDERER=pixman

 

# Run on specific DRM device

export WLR_DRM_DEVICES=/dev/dri/card1

 

# Run in X11 backend (nested)

export WLR_BACKENDS=x11

 

# Run in headless mode

export WLR_BACKENDS=headless

```

 

---

 

## Next Steps for POC 1+

 

Once POC 0 (skeleton compositor) is complete, consider:

 

### POC 1: Basic Window Management

- Window focus and activation

- Window stacking and z-order

- Basic tiling/floating layouts

- Window close/minimize/maximize

 

### POC 2: Multi-Monitor Support

- Multiple output configuration

- Output hotplug handling

- Per-output workspaces

- Output mirroring/extension

 

### POC 3: Advanced Features

- Layer shell for panels/backgrounds

- XWayland support

- Fractional scaling

- Damage tracking optimization

 

### POC 4: QML UI (Transition to waylib)

- QML-based compositor UI

- Custom window decorations

- Animations and effects

- Configuration management

 

---

 

## References

 

### Official Documentation

- **wlroots:** https://gitlab.freedesktop.org/wlroots/wlroots

- **Wayland Protocol:** https://wayland.freedesktop.org/docs/html/

- **Qt Documentation:** https://doc.qt.io/qt-6/

 

### Related Projects

- **treeland:** Full compositor implementation (this repository)

- **qwlroots:** Qt wrapper for wlroots (this repository)

- **waylib:** High-level compositor framework (this repository)

 

### Example Compositors

- **tinywl:** Minimal reference compositor (wlroots)

- **sway:** i3-compatible Wayland compositor

- **wayfire:** 3D Wayland compositor

- **kwin:** KDE Plasma Wayland compositor

 

---

 

## Appendix: File Sizes

 

### qwlroots tinywl

- **main.cpp:** 685 lines

- **CMakeLists.txt:** 27 lines

- **Total:** ~712 lines

 

### waylib tinywl

- **main.cpp:** 55 lines

- **helper.h:** 191 lines

- **helper.cpp:** ~500 lines (estimated)

- **Additional C++ files:** ~2000 lines (estimated)

- **QML files:** ~1000 lines (estimated)

- **CMakeLists.txt:** 83 lines

- **Total:** ~3800 lines (estimated)

 

### Comparison

The qwlroots tinywl is approximately **5x smaller** than waylib tinywl, making it ideal for learning and POC development.

 

---

 

## Glossary

 

- **Compositor:** Software that combines window surfaces into final screen image

- **Backend:** Hardware abstraction (DRM, X11, Wayland, Headless)

- **Renderer:** Graphics rendering system (GLES2, Vulkan, Pixman)

- **Allocator:** Buffer allocation system (GBM, DRM)

- **Surface:** Rectangular area that can be rendered

- **Output:** Physical or virtual display

- **Seat:** Collection of input devices (keyboard, mouse, touch)

- **Scene Graph:** Tree structure for efficient rendering

- **XDG Shell:** Standard Wayland protocol for desktop windows

- **Layer Shell:** Protocol for surfaces at specific layers (background, panel, overlay)

- **XWayland:** X11 compatibility layer for Wayland

 

---

 

**End of Research Documentation**
