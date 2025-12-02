# Web Compositor - POC 0: Skeleton Project

A foundational Qt6.10 Wayland compositor using waylib-shared as a submodule.

## Project Structure

```
webcompositor/
├── CMakeLists.txt              # Root build configuration
├── cmake/
│   └── FindWaylib.cmake        # Custom find module (optional)
├── src/
│   ├── CMakeLists.txt
│   └── main.cpp                # Minimal entry point stub
├── qml/
│   └── main.qml                # Empty QML shell
└── external/
    └── waylib-shared/          # Git submodule
```

## Prerequisites

### System Requirements
- Fedora 43 (or compatible Linux distribution)
- CMake >= 3.25
- GCC/Clang with C++20 support

### Qt6.10+ Dependencies
```bash
sudo dnf install \
    qt6-qtbase-devel \
    qt6-qtdeclarative-devel \
    cmake \
    gcc-c++
```

### Waylib-shared Runtime Dependencies
```bash
sudo dnf install \
    wlroots-devel \
    wayland-devel \
    wayland-protocols-devel \
    libdrm-devel \
    pixman-devel \
    libxkbcommon-devel
```

## Build Instructions

### 1. Initialize Submodules
```bash
git submodule update --init --recursive
```

This will clone the waylib-shared submodule which includes:
- qwlroots (Qt wrappers for wlroots)
- waylib (High-level compositor framework)

### 2. Configure with CMake
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

Expected output:
- Qt6.10 modules discovered (Core, Gui, Qml, Quick)
- waylib-shared submodule configured
- `compile_commands.json` generated

### 3. Build
```bash
cmake --build build
```

This will produce:
- `build/src/webcompositor` executable
- Linked against Qt6 and Waylib (if submodule initialized)

### 4. Run
```bash
./build/src/webcompositor
```

The application should:
- Display an empty 640x480 window with title "Web Compositor - POC 0"
- Exit cleanly when closed
- **NOT** initialize any Wayland protocols (this is POC 0)

## Configuration Options

### Use System Waylib (instead of submodule)
```bash
cmake -B build -DWITH_SUBMODULE_WAYLIB=OFF
```

## Success Criteria

- [x] CMake project structure created
- [x] Root CMakeLists.txt with Qt6.10 configuration
- [x] Waylib-shared submodule integrated
- [x] Minimal main.cpp (under 20 lines)
- [x] Empty QML shell
- [ ] CMake configures without errors (requires Qt6.10 installed)
- [ ] `compile_commands.json` generated
- [ ] Executable links successfully

## Constraints (POC 0)

- ✅ No Wayland protocol initialization
- ✅ No WServer or qwlroots API calls
- ✅ No WebEngine dependencies
- ✅ main.cpp under 20 lines (currently 9 lines)

## Next Steps (Agent 2+)

POC 0 establishes only the build infrastructure. Future agents will:
- **Agent 2**: Initialize Waylib/WServer for basic compositor functionality
- **Agent 3**: Integrate Qt WebEngine for web content rendering
- **Agent 4**: Implement WebChannel bridge for JS↔C++ communication
- **Agent 5**: Integration testing

## Troubleshooting

### Qt6.10 not found
Ensure Qt6.10+ is installed. Check with:
```bash
cmake --find-package -DNAME=Qt6 -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=VERSION
```

### Waylib submodule not initialized
```bash
git submodule update --init --recursive
```

### Build errors
Check that all dependencies are installed:
```bash
pkg-config --modversion wlroots wayland-server pixman-1
```
