# Agent 1: Qt Scaffold

## Implements
- POC-0: Skeleton Project

## Scope
Create the foundational CMake project structure for a Qt6.10 Wayland compositor using waylib-shared as a submodule. This agent establishes build infrastructure only — no compositor logic.

## Deliverables

### 1. Repository Structure
```
webcompositor/
├── CMakeLists.txt              # Root build configuration
├── cmake/
│   └── FindWaylib.cmake        # Custom find module (if needed)
├── src/
│   ├── CMakeLists.txt
│   └── main.cpp                # Minimal entry point stub
├── qml/
│   └── main.qml                # Empty QML shell
└── external/
    └── waylib-shared/          # Git submodule
```

### 2. Root CMakeLists.txt Requirements
```cmake
cmake_minimum_required(VERSION 3.25)
project(webcompositor VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt6.10 minimum
find_package(Qt6 6.10 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
)

# Submodule integration
option(WITH_SUBMODULE_WAYLIB "Use waylib-shared from submodule" ON)
if(WITH_SUBMODULE_WAYLIB)
    set(WITH_SUBMODULE_QWLROOTS ON)
    add_subdirectory(external/waylib-shared/waylib)
endif()
```

### 3. Minimal main.cpp
```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

### 4. Build Verification
- `cmake -B build -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build`
- Binary executes without crash (displays empty window or exits cleanly)

## Success Criteria
- [ ] CMake configures without errors on Fedora 43
- [ ] Qt6.10 modules discovered
- [ ] waylib-shared submodule compiles as dependency
- [ ] `compile_commands.json` generated
- [ ] Executable links successfully

## Constraints
- Do NOT initialize Wayland protocols
- Do NOT call WServer or qwlroots APIs
- Do NOT add WebEngine dependencies yet
- Keep main.cpp under 20 lines
