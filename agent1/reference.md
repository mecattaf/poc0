# External References

## waylib-shared Repository
- **URL**: https://github.com/vioken/waylib-shared
- **Branch**: master
- **Action**: ADOPT
- **What**: Complete submodule structure. Use as-is for `external/waylib-shared/`.
- **Files to study**:
  - `CMakeLists.txt` (root) — submodule integration pattern
  - `waylib/CMakeLists.txt` — Qt module dependencies

## qwlroots Examples
- **URL**: https://github.com/vioken/waylib-shared/tree/master/qwlroots/examples/tinywl
- **Action**: REFERENCE ONLY (for Agent 2)
- **What**: Do not copy code. Only observe CMakeLists.txt structure for minimal compositor target.

## Qt6 CMake Documentation
- **URL**: https://doc.qt.io/qt-6/cmake-manual.html
- **Action**: ADOPT
- **What**: Follow Qt6 CMake best practices:
  - `qt_standard_project_setup()`
  - `qt_add_executable()`
  - `qt_add_qml_module()`

## Treeland Build Configuration
- **URL**: https://github.com/vioken/waylib-shared/blob/master/CMakeLists.txt
- **Action**: ADAPT
- **What**: Copy the submodule integration pattern:
```cmake
if(WITH_SUBMODULE_WAYLIB)
    set(WITH_SUBMODULE_QWLROOTS ON)
    set(BUILD_SHARED_LIBS_WAYLIB ${BUILD_SHARED_LIBS})
    set(BUILD_SHARED_QWLROOTS_LIBS OFF)
    add_subdirectory(waylib)
endif()
```
- **Adaptation**: Change paths to `external/waylib-shared/waylib`

## Fedora Qt6.10 Packages
- **URL**: https://packages.fedoraproject.org/pkgs/qt6/
- **Action**: REFERENCE
- **What**: Verify package names for spec file dependencies:
  - `qt6-qtbase-devel`
  - `qt6-qtdeclarative-devel`
  - `qt6-qtwayland-devel`

## REJECT

### quickshell-webengine-git patch
- **URL**: (local patch file)
- **Action**: REJECT for Agent 1
- **Why**: WebEngine integration is Agent 3 scope. Do not add WebEngine CMake configuration yet.

### Treeland full CMakeLists.txt
- **Action**: REJECT
- **Why**: Too complex. Contains DDM, plugins, D-Bus, protocols. Agent 1 needs minimal scaffold only.
