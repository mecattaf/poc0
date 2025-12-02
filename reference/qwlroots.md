# QWlroots Repository Research Report

## 1. What is qwlroots?

qwlroots is a Qt-style C++ binding for wlroots, a modular Wayland compositor library. It provides:

- **Qt Integration**: Wraps wlroots structs as C++ classes with Qt object semantics
- **Signal/Slot System**: Converts Wayland's wl_signal to Qt signals
- **Simplified API**: Makes wlroots accessible to Qt developers with familiar patterns
- **Version Support**: Currently compatible with wlroots 0.18.x and 0.19.x
- **Coverage**: 80.6% of wlroots types wrapped (83 out of 103 types)

## 2. Complete Public API Headers Organized by Category

### Core Classes (/home/user/qwlroots/src/)
- **qwglobal.h** - Global definitions, macros, and wrapping templates
- **qwobject.h** - Base object class with Qt integration
- **qwdisplay.h** - Wayland display wrapper
- **qwbackend.h** - Backend management

### Types (/home/user/qwlroots/src/types/)

**Compositor & Surfaces:**
- **qwcompositor.h** - `qw_compositor`, `qw_surface`
- **qwsubcompositor.h** - `qw_subcompositor`, `qw_subsurface`
- **qwscene.h** - Scene graph: `qw_scene`, `qw_scene_node`, `qw_scene_surface`, `qw_scene_output`, `qw_scene_tree`, `qw_scene_rect`, `qw_scene_buffer`

**Output Management:**
- **qwoutput.h** - `qw_output`, `qw_output_cursor`, `qw_output_state`
- **qwoutputlayout.h** - `qw_output_layout`
- **qwoutputlayer.h** - `qw_output_layer`
- **qwoutputmanagementv1.h** - Output management protocol
- **qwoutputpowermanagementv1.h** - Power management protocol

**XDG Shell:**
- **qwxdgshell.h** - `qw_xdg_shell`, `qw_xdg_surface`, `qw_xdg_popup`, `qw_xdg_toplevel`
- **qwxdgactivationv1.h** - Activation protocol
- **qwxdgdecorationmanagerv1.h** - Server-side decorations
- **qwxdgoutputv1.h** - Output info protocol
- **qwxdgforeignv1.h**, **qwxdgforeignv2.h**, **qwxdgforeignregistry.h** - Foreign toplevel

**Layer Shell:**
- **qwlayershellv1.h** - `qw_layer_shell_v1`, `qw_layer_surface_v1`

**Input Devices:**
- **qwinputdevice.h** - `qw_input_device`, `qw_keyboard`, `qw_pointer`, `qw_tablet`, `qw_tablet_pad`, `qw_switch`, `qw_touch`
- **qwkeyboard.h** - Keyboard handling
- **qwpointer.h** - Pointer handling
- **qwtouch.h** - Touch handling
- **qwtablet.h**, **qwtabletpad.h** - Tablet input

**Seat & Input Management:**
- **qwseat.h** - `qw_seat`, `qw_seat_client`
- **qwcursor.h** - `qw_cursor`
- **qwkeyboardgroup.h** - Keyboard grouping
- **qwxcursormanager.h** - X cursor management

**Buffers & Memory:**
- **qwbuffer.h** - `qw_buffer`, `qw_client_buffer`
- **qwshm.h** - Shared memory buffers
- **qwsinglepixelbufferv1.h** - Single pixel buffers
- **qwdamagering.h** - Damage tracking

**Data Transfer:**
- **qwdatadevice.h** - `qw_drag`, `qw_drag_icon`, `qw_data_device_manager`
- **qwdatacontrolv1.h** - Data control protocol
- **qwprimaryselection.h**, **qwprimaryselectionv1.h** - Primary selection

**Protocols:**
- **qwdrm.h** - DRM protocol
- **qwdrmleasev1.h** - DRM leasing
- **qwlinuxdmabufv1.h** - Linux DMABUF
- **qwlinuxdrmsyncobjv1.h** - DRM syncobj
- **qwviewporter.h** - Viewport scaling
- **qwfractionalscalemanagerv1.h** - Fractional scaling
- **qwpointerconstraintsv1.h** - Pointer constraints
- **qwpointergesturesv1.h** - Pointer gestures
- **qwrelativepointerv1.h** - Relative pointer
- **qwkeyboardshortcutsinhibitv1.h** - Keyboard shortcuts inhibitor
- **qwidleinhibitv1.h** - Idle inhibitor
- **qwidlenotifyv1.h** - Idle notification
- **qwpresentation.h** - Presentation time
- **qwscreencopyv1.h** - Screen copy
- **qwexportdmabufv1.h** - DMABUF export
- **qwextimagecopycapturev1.h** - Image copy capture
- **qwsessionlockv1.h** - Session lock
- **qwtearingcontrolv1.h** - Tearing control
- **qwcontenttypev1.h** - Content type hints
- **qwalphamodifierv1.h** - Alpha modifier
- **qwcolormanagerv1.h** - Color management
- **qwgammacontorlv1.h** - Gamma control
- **qwsecuritycontextmanagerv1.h** - Security context
- **qwcursorshapev1.h** - Cursor shape
- **qwtransientseatv1.h** - Transient seat

**Input Method:**
- **qwtextinputv3.h** - Text input protocol
- **qwinputmethodv2.h** - Input method protocol
- **qwvirtualkeyboardv1.h** - Virtual keyboard
- **qwvirtualpointerv1.h** - Virtual pointer

**Tablet:**
- **qwtabletv2.h** - Tablet v2 protocol

**Xwayland:**
- **qwxwayland.h** - Xwayland integration
- **qwxwaylandserver.h** - Xwayland server
- **qwxwaylandsurface.h** - Xwayland surface
- **qwxwaylandshellv1.h** - Xwayland shell

**Foreign Toplevel:**
- **qwforeigntoplevelhandlev1.h** - Foreign toplevel handle
- **qwextforeigntoplevellistv1.h** - Foreign toplevel list

**Misc:**
- **qwfullscreenshellv1.h** - Fullscreen shell

### Render (/home/user/qwlroots/src/render/)
- **qwallocator.h** - `qw_allocator`
- **qwrenderer.h** - `qw_renderer`
- **qwtexture.h** - `qw_texture`
- **qwswapchain.h** - `qw_swapchain`
- **qwegl.h** - `qw_egl`
- **qwcolor.h** - Color management
- **qwdmabuf.h** - DMABUF rendering
- **qwdrmformatset.h** - DRM format set
- **qwdrmsyncobj.h** - DRM sync objects

### Utilities (/home/user/qwlroots/src/util/)
- **qwbox.h** - `qw_box`, `qw_fbox` (Qt geometry type conversions)
- **qwsignalconnector.h** - `qw_signal_connector` (Wayland signal to Qt signal bridge)
- **qwlogging.h** - `qw_log` (wlroots logging integration)

### Interfaces (/home/user/qwlroots/src/interfaces/)
- **qwinterface.h** - Base interface template
- **qwbackendinterface.h** - Backend interface
- **qwbufferinterface.h** - Buffer interface
- **qwkeyboardinterface.h** - Keyboard interface
- **qwoutputinterface.h** - Output interface
- **qwpointerinterface.h** - Pointer interface
- **qwrendererinterface.h** - Renderer interface
- **qwswitchinterface.h** - Switch interface
- **qwtabletpadinterface.h** - Tablet pad interface

## 3. QWOutput and Surface Qt Mappings

### QWOutput (qw_output)

**File:** /home/user/qwlroots/src/types/qwoutput.h

**Class Definition:**
```cpp
class QW_CLASS_OBJECT(output)  // Expands to: qw_output : public qw_object<wlr_output, qw_output>
{
    QW_OBJECT
    Q_OBJECT

    // Qt Signals (converted from wlroots events)
    QW_SIGNAL(frame)
    QW_SIGNAL(damage, wlr_output_event_damage*)
    QW_SIGNAL(needs_frame)
    QW_SIGNAL(precommit, wlr_output_event_precommit*)
    QW_SIGNAL(commit, wlr_output_event_commit*)
    QW_SIGNAL(present, wlr_output_event_present*)
    QW_SIGNAL(bind, wlr_output_event_bind*)
    QW_SIGNAL(description)
    QW_SIGNAL(request_state, wlr_output_event_request_state*)
```

**Qt Integration:**
- Inherits from `QObject` (via `qw_object` template)
- Emits Qt signals for all wlroots output events
- Automatic lifecycle management: destroyed when underlying wlr_output is destroyed
- Signal `before_destroy()` emitted before destruction

**Key Methods:**
```cpp
// Backend detection
QW_FUNC_MEMBER(output, is_drm, bool)
QW_FUNC_MEMBER(output, is_wl, bool)
QW_FUNC_MEMBER(output, is_headless, bool)

// Configuration
QW_FUNC_MEMBER(output, init_render, bool, wlr_allocator*, wlr_renderer*)
QW_FUNC_MEMBER(output, set_name, void, const char*)
QW_FUNC_MEMBER(output, set_description, void, const char*)

// State management (wlroots 0.18+)
QW_FUNC_MEMBER(output, test_state, bool, const wlr_output_state*)
QW_FUNC_MEMBER(output, commit_state, bool, const wlr_output_state*)
```

**Helper Classes:**
```cpp
// qw_output_cursor - REINTERPRET_CAST pattern
class QW_CLASS_REINTERPRET_CAST(output_cursor) {
    QW_FUNC_STATIC(output_cursor, create, qw_output_cursor*, wlr_output*)
    QW_FUNC_MEMBER(output_cursor, set_buffer, bool, wlr_buffer*, ...)
    QW_FUNC_MEMBER(output_cursor, move, bool, double x, double y)
};

// qw_output_state - BOX pattern
class QW_CLASS_BOX(output_state) {
    QW_FUNC_MEMBER(output_state, set_enabled, void, bool)
    QW_FUNC_MEMBER(output_state, set_mode, void, wlr_output_mode*)
    QW_FUNC_MEMBER(output_state, set_scale, void, float)
    // ... other state setters
};
```

### Surface Classes (qw_surface, qw_subsurface)

**File:** /home/user/qwlroots/src/types/qwcompositor.h

**qw_surface:**
```cpp
class QW_CLASS_OBJECT(surface)  // qw_surface : public qw_object<wlr_surface, qw_surface>
{
    QW_OBJECT
    Q_OBJECT

    // Qt Signals
    QW_SIGNAL(client_commit)
    QW_SIGNAL(commit)
    QW_SIGNAL(new_subsurface, wlr_subsurface*)
    QW_SIGNAL(map)
    QW_SIGNAL(unmap)
```

**Key Surface Methods:**
```cpp
// Creation/lookup
QW_FUNC_STATIC(surface, from_resource, qw_surface*, wl_resource*)

// Surface operations
QW_FUNC_MEMBER(surface, for_each_surface, void, wlr_surface_iterator_func_t, void*)
QW_FUNC_MEMBER(surface, get_texture, wlr_texture*)
QW_FUNC_MEMBER(surface, has_buffer, bool)
QW_FUNC_MEMBER(surface, map, void)
QW_FUNC_MEMBER(surface, unmap, void)
QW_FUNC_MEMBER(surface, send_frame_done, void, const timespec*)
QW_FUNC_MEMBER(surface, send_enter, void, wlr_output*)
QW_FUNC_MEMBER(surface, send_leave, void, wlr_output*)
```

**qw_compositor:**
```cpp
class QW_CLASS_OBJECT(compositor)
{
    QW_OBJECT
    Q_OBJECT

    QW_SIGNAL(new_surface, wlr_surface*)  // Emitted when new surface created
```

**Scene Graph Integration (qwscene.h):**

The scene graph provides higher-level surface management:

```cpp
// Base scene node
class qw_scene_node : public qw_object<wlr_scene_node, qw_scene_node> {
    QW_FUNC_MEMBER(scene_node, set_enabled, void, bool)
    QW_FUNC_MEMBER(scene_node, set_position, void, int x, int y)
    // ... positioning and hierarchy management
};

// Surface scene node
class qw_scene_surface : public qw_object<wlr_scene_surface, qw_scene_surface> {
    QW_FUNC_STATIC(scene_surface, create, qw_scene_surface*,
                   wlr_scene_tree* parent, wlr_surface* surface)
};

// Buffer scene node (for direct buffer rendering)
class qw_scene_buffer : public qw_scene_node {
    QW_SIGNAL(outputs_update, wlr_scene_outputs_update_event*)
    QW_SIGNAL(output_enter, wlr_scene_output*)
    QW_SIGNAL(output_leave, wlr_scene_output*)
    QW_SIGNAL(frame_done, timespec*)

    QW_FUNC_MEMBER(scene_buffer, set_buffer, void, wlr_buffer*)
    QW_FUNC_MEMBER(scene_buffer, set_opacity, void, float)
};
```

## 4. Architecture and Design Patterns

### Four Wrapping Patterns

qwlroots uses four distinct patterns to wrap wlroots types:

#### Pattern 1: QW_CLASS_OBJECT (Signal-Emitting Objects)

**When to use:** Types with signals/events

**Template:** `qw_object<Handle, Derive>`

**Features:**
- Full QObject with signals/slots
- Automatic lifecycle management
- Connects to wlroots destroy signals
- Tracked in global object map

**Example:**
```cpp
class QW_CLASS_OBJECT(output)  // Expands to:
// qw_output : public qw_object<wlr_output, qw_output>
{
    QW_OBJECT                    // Protected constructor, friend declarations
    Q_OBJECT                     // Qt meta-object

    QW_SIGNAL(frame)            // Binds wlr_output.events.frame → notify_frame()
    QW_SIGNAL(commit, ...)      // With parameters

public:
    // Automatically provides:
    // - static qw_output* from(wlr_output*)  // Get or create wrapper
    // - static qw_output* get(wlr_output*)   // Get existing wrapper or nullptr
    // - wlr_output* handle() const           // Get underlying handle
    // - operator wlr_output*()               // Implicit conversion
};
```

#### Pattern 2: QW_CLASS_REINTERPRET_CAST (Zero-Overhead Wrappers)

**When to use:** Types without signals, simple wrappers

**Template:** `qw_reinterpret_cast<Handle, Derive>`

**Features:**
- Zero memory overhead (just a cast)
- No QObject, no signals
- Deleted constructor and destructor
- Uses `std::destroying_delete_t` for destruction

**Example:**
```cpp
class QW_CLASS_REINTERPRET_CAST(texture)  // Expands to:
// qw_texture : public qw_reinterpret_cast<wlr_texture, qw_texture>
{
public:
    // Static factory methods
    QW_FUNC_STATIC(texture, from_pixels, qw_texture*, ...)

    // Member functions
    QW_FUNC_MEMBER(texture, update_from_buffer, bool, ...)

    // Automatically provides:
    // - static qw_texture* from(wlr_texture*)  // reinterpret_cast
    // - wlr_texture* handle() const
    // - operator wlr_texture*()

private:
    friend class qw_reinterpret_cast;
    QW_FUNC_MEMBER(texture, destroy, void)  // Called by delete
};
```

#### Pattern 3: QW_CLASS_BOX (Stack-Allocated Wrappers)

**When to use:** Stack objects that wrap wlroots structs (like wlr_output_state)

**Template:** `qw_class_box<Handle, Derive>`

**Features:**
- Contains wlroots struct as member
- Constructor calls init(), destructor calls finish()
- Can be allocated on stack

**Example:**
```cpp
class QW_CLASS_BOX(output_state)  // Expands to:
// qw_output_state : public qw_class_box<wlr_output_state, qw_output_state>
{
public:
    QW_FUNC_MEMBER(output_state, set_enabled, void, bool)
    QW_FUNC_MEMBER(output_state, set_mode, void, wlr_output_mode*)

private:
    friend class qw_class_box;
    QW_FUNC_MEMBER(output_state, init, void)
    QW_FUNC_MEMBER(output_state, finish, void)
};

// Usage:
qw_output_state state;  // Calls wlr_output_state_init()
state.set_mode(mode);
// Destructor calls wlr_output_state_finish()
```

#### Pattern 4: QW_CLASS_INTERFACE (Custom Implementations)

**When to use:** Implementing custom backends/renderers

**Template:** `qw_interface<Handle, Impl>`

**Features:**
- Allows C++ classes to implement wlroots interfaces
- Virtual function binding to C function pointers
- Used for extending wlroots with custom implementations

**Example:**
```cpp
QW_CLASS_INTERFACE(output)  // Generates qw_output_interface

class MyCustomOutput : public qw_output_interface {
    QW_INTERFACE(commit, bool, const wlr_output_state* state) {
        // Your implementation
        return true;
    }
};

// Usage:
auto output = qw_output::create<MyCustomOutput>(args...);
```

### Signal Binding System

The `qw_signal_connector` bridges Wayland's `wl_signal` to Qt signals:

```cpp
class qw_signal_connector {
    // Connects wl_signal to C++ member function
    qw_signal_listener *connect(wl_signal *signal, T *object,
                                void (TSlot::*slot)(Args...));
};
```

**Macro Magic:**
```cpp
#define QW_SIGNAL(name, ...) \
Q_SIGNALS: \
    void notify_##name(__VA_ARGS__);  // Qt signal \
private: \
struct qw_signal_##name { \
    qw_signal_##name(DeriveType *self) { \
        // Binds wlr handle->events.name to this->notify_##name \
        self->bind_signal(&decltype(self->handle()->events)::name,
                         &DeriveType::notify_##name); \
    } \
}; \
qw_signal_##name _signal_##name = this;  // Auto-bind in constructor
```

### Function Binding Macros

**QW_FUNC_STATIC** - Static factory/utility functions:
```cpp
QW_FUNC_STATIC(compositor, create, qw_compositor*, wl_display*, ...)
// Expands to:
static qw_compositor* create(wl_display* display, ...) {
    auto* handle = wlr_compositor_create(display, ...);
    return new qw_compositor(handle, true);  // Owner
}
```

**QW_FUNC_MEMBER** - Member functions:
```cpp
QW_FUNC_MEMBER(output, set_name, void, const char* name)
// Expands to:
void set_name(const char* name) const {
    return wlr_output_set_name(*this, name);  // *this converts to wlr_output*
}
```

### Object Lifecycle Management

**Creation:**
```cpp
// Option 1: from() - Get existing or create new (non-owner)
auto* output = qw_output::from(wlr_handle);

// Option 2: create() - Create as owner
auto* compositor = qw_compositor::create(display, version, renderer);

// Option 3: get() - Get existing or nullptr
auto* output = qw_output::get(wlr_handle);
```

**Ownership:**
- Owner objects call `destroy()` in destructor
- Non-owner objects just clean up Qt resources
- `isHandleOwner` flag tracks ownership

**Destruction:**
```cpp
~qw_object() {
    if (!m_handle) return;

    do_destroy();  // Clean up Qt resources

    if (isHandleOwner) {
        static_cast<Derive*>(this)->Derive::destroy();  // Call wlr destroy
    }
}
```

**Auto-destruction on wlroots destroy:**
```cpp
// Connected in constructor:
sc.connect(&h->events.destroy, this, &qw_object::on_destroy);

inline void on_destroy() {
    Q_EMIT before_destroy();  // Let users clean up first
    do_destroy();
    m_handle = nullptr;
    delete this;  // Self-destruct
}
```

### Global Object Map

All `qw_object` instances are tracked:
```cpp
static QHash<void*, QObject*> map;  // wlr_handle → qw_object

// Lookup:
auto* obj = qw_output::get(wlr_output_ptr);

// Get all objects of type:
auto outputs = qw_output::get_objects();
```

### Qt Type Conversions

**Geometry Types (qwbox.h):**
```cpp
class qw_box {
    explicit qw_box(const wlr_box &box);
    explicit qw_box(const QRect &box);
    QRect toQRect();
    operator wlr_box*();
private:
    wlr_box m_handle;
};

class qw_fbox {
    explicit qw_fbox(const wlr_fbox &box);
    explicit qw_fbox(const QRectF &box);
    QRectF toQRectF();
    operator wlr_fbox*();
};
```

## 5. Key Components and Relationships

### Component Hierarchy

```
qw_display (Wayland display)
    ├── qw_backend (Hardware abstraction)
    │   ├── qw_drm_backend
    │   ├── qw_wayland_backend
    │   ├── qw_x11_backend
    │   ├── qw_libinput_backend
    │   └── qw_headless_backend
    │
    ├── qw_renderer (Rendering)
    │   ├── qw_allocator (Buffer allocation)
    │   ├── qw_texture
    │   └── qw_swapchain
    │
    ├── qw_output (Display output)
    │   ├── qw_output_layout (Multi-output positioning)
    │   ├── qw_output_state (Configuration state)
    │   └── qw_output_cursor
    │
    ├── qw_compositor (Compositor protocol)
    │   ├── qw_surface (Wayland surface)
    │   └── qw_subcompositor
    │       └── qw_subsurface
    │
    ├── qw_scene (Scene graph)
    │   ├── qw_scene_node (Abstract node)
    │   │   ├── qw_scene_tree (Container)
    │   │   ├── qw_scene_rect (Solid color)
    │   │   ├── qw_scene_buffer (Direct buffer)
    │   │   └── qw_scene_surface (Wayland surface)
    │   └── qw_scene_output (Scene output binding)
    │
    ├── qw_seat (Input seat)
    │   ├── qw_keyboard
    │   ├── qw_pointer
    │   ├── qw_touch
    │   └── qw_cursor (Unified cursor)
    │
    ├── qw_xdg_shell (Desktop shell protocol)
    │   ├── qw_xdg_surface
    │   ├── qw_xdg_toplevel (Top-level windows)
    │   └── qw_xdg_popup (Popup windows)
    │
    └── qw_buffer (Buffer management)
        ├── qw_client_buffer
        └── qw_shm (Shared memory)
```

### Typical Usage Flow

1. **Initialize Display:**
```cpp
qw_display display;
display.add_socket_auto();
```

2. **Create Backend:**
```cpp
auto* backend = qw_backend::autocreate(display.get_event_loop(), &session);
connect(backend, &qw_backend::notify_new_output,
        this, &Compositor::handleNewOutput);
backend->start();
```

3. **Setup Renderer:**
```cpp
auto* renderer = qw_renderer::autocreate(backend);
auto* allocator = qw_allocator::autocreate(backend, renderer);
```

4. **Create Compositor:**
```cpp
auto* compositor = qw_compositor::create(&display, 6, renderer);
connect(compositor, &qw_compositor::notify_new_surface,
        this, &Compositor::handleNewSurface);
```

5. **Setup Output:**
```cpp
void handleNewOutput(wlr_output* wlr_out) {
    auto* output = qw_output::from(wlr_out);
    output->init_render(allocator, renderer);

    connect(output, &qw_output::notify_frame,
            this, &Compositor::handleFrame);

    output->create_global();
}
```

6. **Handle Surfaces:**
```cpp
void handleNewSurface(wlr_surface* wlr_surf) {
    auto* surface = qw_surface::from(wlr_surf);

    connect(surface, &qw_surface::notify_commit,
            this, &Compositor::handleSurfaceCommit);
    connect(surface, &qw_surface::notify_map,
            this, &Compositor::handleSurfaceMap);
}
```

### Version Compatibility Handling

qwlroots handles multiple wlroots versions using preprocessor conditionals:

```cpp
#if WLR_VERSION_MINOR >= 18
    QW_SIGNAL(new_toplevel, wlr_xdg_toplevel*)
#endif

#if WLR_VERSION_MINOR < 18
    QW_FUNC_MEMBER(output, enable, void, bool enable)
#endif
```

## 6. Code Examples Showing Qt Integration

### Example 1: Creating and Using an Output

```cpp
// Output wrapper with Qt signals
auto* output = qw_output::from(wlr_output_handle);

// Connect to frame signal (painted every frame)
connect(output, &qw_output::notify_frame, this, [output]() {
    // Render frame
});

// Connect to commit signal
connect(output, &qw_output::notify_commit,
        this, &MyCompositor::onOutputCommit);

// Qt-style method calls
output->set_name("HDMI-1");
output->create_global();

// Check backend type
if (output->is_drm()) {
    // DRM-specific code
}

// Use output state for configuration
qw_output_state state;
state.set_enabled(true);
state.set_scale(2.0f);
output->commit_state(state);
```

### Example 2: Surface Event Handling

```cpp
void MyCompositor::handleNewSurface(wlr_surface* wlr_surf) {
    auto* surface = qw_surface::from(wlr_surf);

    // Store custom data with the surface
    surface->set_data(this, myCustomData);

    // Connect Qt signals
    connect(surface, &qw_surface::notify_commit, this, [surface]() {
        qDebug() << "Surface committed, has buffer:" << surface->has_buffer();

        // Send frame callback
        timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        surface->send_frame_done(&now);
    });

    connect(surface, &qw_surface::notify_map, this, [surface]() {
        qDebug() << "Surface mapped";
        surface->send_enter(m_output);
    });

    connect(surface, &qw_surface::notify_unmap, this, [surface]() {
        qDebug() << "Surface unmapped";
    });

    connect(surface, &qw_surface::before_destroy, this, [this, surface]() {
        // Clean up before wlroots destroys the surface
        auto* data = surface->get_data<MyData>();
        delete data;
    });
}
```

### Example 3: Scene Graph Usage

```cpp
// Create scene
auto* scene = qw_scene::create();
scene->set_linux_dmabuf_v1(m_linux_dmabuf);

// Create scene output
auto* scene_output = qw_scene_output::create(scene, m_output);

// Create surface node in scene
auto* xdg_surface = qw_xdg_surface::from(wlr_xdg);
auto* scene_tree = qw_scene::xdg_surface_create(scene, xdg_surface);

// Connect to buffer signals
connect(scene_buffer, &qw_scene_buffer::notify_output_enter,
        this, [](wlr_scene_output* output) {
    qDebug() << "Buffer entered output";
});

// Render scene
qw_scene_output_state_options options{};
scene_output->commit(&options);
```

### Example 4: Input Handling with Seat

```cpp
auto* seat = qw_seat::create(&display, "seat0");

// Connect input signals
connect(seat, &qw_seat::notify_request_set_cursor,
        this, &MyCompositor::handleSetCursor);

connect(seat, &qw_seat::notify_request_start_drag,
        this, &MyCompositor::handleStartDrag);

// Setup keyboard
connect(backend, &qw_backend::notify_new_input,
        this, [seat](wlr_input_device* dev) {
    if (dev->type == WLR_INPUT_DEVICE_KEYBOARD) {
        auto* keyboard = qw_keyboard::from(dev);

        // Connect keyboard signals
        connect(keyboard, &qw_keyboard::notify_key,
                this, &MyCompositor::handleKey);

        seat->set_keyboard(keyboard);
    }
});

// Setup cursor
auto* cursor = qw_cursor::create();
cursor->attach_output_layout(m_output_layout);

connect(cursor, &qw_cursor::notify_motion,
        this, &MyCompositor::handleCursorMotion);
connect(cursor, &qw_cursor::notify_button,
        this, &MyCompositor::handleCursorButton);
```

### Example 5: XDG Shell Protocol

```cpp
auto* xdg_shell = qw_xdg_shell::create(&display, 6);

connect(xdg_shell, &qw_xdg_shell::notify_new_surface,
        this, [this](wlr_xdg_surface* wlr_xdg) {
    auto* xdg_surface = qw_xdg_surface::from(wlr_xdg);

    connect(xdg_surface, &qw_xdg_surface::notify_configure,
            this, &MyCompositor::handleConfigure);

    // Handle toplevel
    if (wlr_xdg->role == WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
        auto* toplevel = qw_xdg_toplevel::from(wlr_xdg->toplevel);

        connect(toplevel, &qw_xdg_toplevel::notify_request_maximize,
                this, [toplevel]() {
            toplevel->set_maximized(true);
            qDebug() << "Toplevel" << toplevel->handle()->title << "maximized";
        });

        connect(toplevel, &qw_xdg_toplevel::notify_request_fullscreen,
                this, &MyCompositor::handleFullscreen);

        connect(toplevel, &qw_xdg_toplevel::notify_set_title,
                this, [](char* title) {
            qDebug() << "Window title:" << title;
        });
    }
});
```

### Example 6: Qt Geometry Integration

```cpp
// Convert between Qt and wlroots geometry
QRect qtRect(100, 100, 800, 600);
qw_box box(qtRect);

// Use with wlroots functions
cursor->map_to_region(box);

// Convert back
wlr_box wlr_box = *output->handle();
QRect outputRect = qw_box(wlr_box).toQRect();

// Floating point version
QRectF qtRectF(0.0, 0.0, 1920.5, 1080.5);
qw_fbox fbox(qtRectF);
```

### Example 7: Custom Backend Implementation

```cpp
class MyOutputInterface : public qw_output_interface {
    QW_INTERFACE(commit, bool, const wlr_output_state* state) override {
        qDebug() << "Custom output commit";
        // Your rendering implementation
        return true;
    }

    QW_INTERFACE(destroy, void) override {
        qDebug() << "Custom output destroy";
        // Cleanup
    }
};

// Create custom output
auto* output = qw_output::create<MyOutputInterface>(args...);
```

## 7. Summary

qwlroots provides a comprehensive Qt wrapper for wlroots with:

1. **80.6% Coverage**: 83 out of 103 wlroots types wrapped
2. **Four Wrapping Patterns**: Object, ReinterpretCast, Box, Interface
3. **Full Qt Integration**: QObject, signals/slots, Qt types
4. **Automatic Lifecycle**: Wrapper objects track wlroots lifecycle
5. **Type Safety**: C++ templates with compile-time checks
6. **Zero/Low Overhead**: ReinterpretCast for zero overhead, Object for features

The library successfully bridges the gap between wlroots' C API and Qt's C++ ecosystem, making Wayland compositor development accessible to Qt developers while maintaining the flexibility and performance of wlroots.
