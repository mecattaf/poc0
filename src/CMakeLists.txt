# Qt standard project setup
qt_standard_project_setup(REQUIRES 6.10)

# Find pkg-config dependencies FIRST
find_package(PkgConfig REQUIRED)
pkg_check_modules(WLROOTS REQUIRED IMPORTED_TARGET wlroots-0.19)
pkg_check_modules(WAYLAND_SERVER REQUIRED IMPORTED_TARGET wayland-server)
pkg_check_modules(PIXMAN REQUIRED IMPORTED_TARGET pixman-1)

message(STATUS "Found wlroots: ${WLROOTS_VERSION}")
message(STATUS "Found wayland-server: ${WAYLAND_SERVER_VERSION}")

# CRITICAL: Add include directories BEFORE linking targets
# Use PROJECT_SOURCE_DIR for reliability
set(WAYLIB_SRC_DIR "${PROJECT_SOURCE_DIR}/external/waylib-shared/waylib/src/server")
set(QWLROOTS_SRC_DIR "${PROJECT_SOURCE_DIR}/external/waylib-shared/qwlroots/src")

# ==========================================
# Target 1: webcompositor (The Wayland Server)
# ==========================================
qt_add_executable(webcompositor
    compositor/main.cpp
    compositor/compositor.h
    compositor/compositor.cpp
)

# Add ALL include directories for waylib and qwlroots
target_include_directories(webcompositor PRIVATE
    ${WAYLIB_SRC_DIR}/kernel
    ${WAYLIB_SRC_DIR}/qtquick
    ${WAYLIB_SRC_DIR}/protocols
    ${WAYLIB_SRC_DIR}/utils
    ${WAYLIB_SRC_DIR}
    ${QWLROOTS_SRC_DIR}
    ${QWLROOTS_SRC_DIR}/types
    ${QWLROOTS_SRC_DIR}/render
    ${QWLROOTS_SRC_DIR}/util
    ${QWLROOTS_SRC_DIR}/interfaces
    ${CMAKE_BINARY_DIR}/external/waylib-shared/waylib/src/server
    ${CMAKE_BINARY_DIR}/external/waylib-shared/qwlroots/src
    ${WLROOTS_INCLUDE_DIRS}
    ${WAYLAND_SERVER_INCLUDE_DIRS}
)

# Link Qt libraries for Compositor
target_link_libraries(webcompositor
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    # Note: WebEngine is NOT linked here anymore!
)

# Link pkg-config dependencies
target_link_libraries(webcompositor PRIVATE 
    PkgConfig::WLROOTS
    PkgConfig::WAYLAND_SERVER
    PkgConfig::PIXMAN
)

# Link waylib and qwlroots
if(TARGET WaylibSharedServer)
    target_link_libraries(webcompositor PRIVATE WaylibSharedServer)
elseif(TARGET Waylib::SharedServer)
    target_link_libraries(webcompositor PRIVATE Waylib::SharedServer)
endif()

if(TARGET qwlroots)
    target_link_libraries(webcompositor PRIVATE qwlroots)
elseif(TARGET QWlroots::QWlroots)
    target_link_libraries(webcompositor PRIVATE QWlroots::QWlroots)
endif()

# ==========================================
# Target 2: web-shell (The WebEngine Client)
# ==========================================
qt_add_executable(web-shell
    client/main.cpp
)

# Add QML module for the client
qt_add_qml_module(web-shell
    URI WebShell
    VERSION 1.0
    QML_FILES
        client/qml/main.qml
    RESOURCES
        html/test.html
)

# Link Qt libraries for Client
target_link_libraries(web-shell
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::WebEngineQuick
    Qt6::WebChannel
)

target_compile_definitions(web-shell PRIVATE
    QT_WEBENGINE_ENABLED
)
