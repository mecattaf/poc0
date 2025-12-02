# Required Reading

## Primary Sources

### waylib-shared Build System
- `waylib-shared/CMakeLists.txt` — Root build configuration
- `waylib-shared/waylib/CMakeLists.txt` — Waylib library configuration  
- `waylib-shared/qwlroots/CMakeLists.txt` — qwlroots configuration

### Key CMake Variables
```cmake
# From waylib-shared root:
WITH_SUBMODULE_WAYLIB=ON        # Use bundled waylib
WITH_SUBMODULE_QWLROOTS=ON      # Use bundled qwlroots
BUILD_SHARED_LIBS=ON            # Shared library build
BUILD_WAYLIB_EXAMPLES=OFF       # Skip examples for faster build
BUILD_QWLROOTS_EXAMPLES=OFF     # Skip qwlroots examples

# qwlroots specific:
USE_WLROOTS_19=ON               # wlroots 0.19 compatibility (default)
DISABLE_XWAYLAND=OFF            # Keep XWayland support
```

### Qt6.10 Module Requirements
```
Qt6::Core
Qt6::Gui  
Qt6::Qml
Qt6::Quick
Qt6::GuiPrivate          # Required by waylib
Qt6::QuickPrivate        # Required by waylib
```

## Key Constraints

### Fedora 43 Package Dependencies
```bash
# Build requirements
cmake >= 3.25
gcc-c++ >= 13  # C++20 support
qt6-qtbase-devel >= 6.10
qt6-qtdeclarative-devel >= 6.10

# waylib-shared runtime deps
wlroots-devel >= 0.18
wayland-devel
wayland-protocols-devel
libdrm-devel
pixman-devel
libxkbcommon-devel
```

### Submodule Initialization
```bash
git submodule add https://github.com/vioken/waylib-shared external/waylib-shared
git submodule update --init --recursive
```

## Architecture Notes

### Why Submodule Approach
- waylib-shared tracks wlroots changes rapidly
- System packages lag behind
- Ensures qwlroots + waylib version compatibility
- Single `add_subdirectory()` integrates full stack

### Build Output Structure
```
build/
├── src/webcompositor           # Main executable
├── external/waylib-shared/
│   ├── waylib/libWaylib.so
│   └── qwlroots/libQWlroots.a  # Static by default
└── compile_commands.json
```
