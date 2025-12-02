# Qt standard project setup
qt_standard_project_setup(REQUIRES 6.10)

# Create executable
qt_add_executable(webcompositor
    main.cpp
    compositor.h
    compositor.cpp
)

# Add QML module
qt_add_qml_module(webcompositor
    URI WebCompositor
    VERSION 1.0
    QML_FILES
        ../qml/main.qml
    RESOURCES
        ../html/test.html
)

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

# Debug: Print paths to verify they're correct
message(STATUS "WAYLIB_SRC_DIR: ${WAYLIB_SRC_DIR}")
message(STATUS "QWLROOTS_SRC_DIR: ${QWLROOTS_SRC_DIR}")

# Verify directories exist
if(NOT EXISTS "${WAYLIB_SRC_DIR}/kernel/wserver.h")
    message(FATAL_ERROR "Cannot find wserver.h at ${WAYLIB_SRC_DIR}/kernel/wserver.h - submodule may not be initialized")
endif()
if(NOT EXISTS "${QWLROOTS_SRC_DIR}/qwlogging.h")
    message(FATAL_ERROR "Cannot find qwlogging.h at ${QWLROOTS_SRC_DIR}/qwlogging.h - submodule may not be initialized")
endif()

message(STATUS "Found waylib headers at: ${WAYLIB_SRC_DIR}")
message(STATUS "Found qwlroots headers at: ${QWLROOTS_SRC_DIR}")

# Add ALL include directories for waylib and qwlroots
target_include_directories(webcompositor PRIVATE
    # Waylib server headers - kernel (wserver.h, wbackend.h, woutput.h, wseat.h)
    ${WAYLIB_SRC_DIR}/kernel
    
    # Waylib server headers - qtquick (wrenderhelper.h, woutputrenderwindow.h)
    ${WAYLIB_SRC_DIR}/qtquick
    
    # Waylib server headers - protocols
    ${WAYLIB_SRC_DIR}/protocols
    
    # Waylib server headers - utils
    ${WAYLIB_SRC_DIR}/utils
    
    # Waylib server headers - root (for any headers at server level)
    ${WAYLIB_SRC_DIR}
    
    # qwlroots headers - root (qwlogging.h, qwbackend.h, qwdisplay.h, etc.)
    ${QWLROOTS_SRC_DIR}
    
    # qwlroots headers - types (qwoutput.h, qwoutputlayout.h, etc.)
    ${QWLROOTS_SRC_DIR}/types
    
    # qwlroots headers - render (qwallocator.h, qwrenderer.h)
    ${QWLROOTS_SRC_DIR}/render
    
    # qwlroots headers - util (qwlogging.h is also here)
    ${QWLROOTS_SRC_DIR}/util
    
    # qwlroots headers - interfaces
    ${QWLROOTS_SRC_DIR}/interfaces

    # Generated headers from build directory (for moc files, etc.)
    ${CMAKE_BINARY_DIR}/external/waylib-shared/waylib/src/server
    ${CMAKE_BINARY_DIR}/external/waylib-shared/qwlroots/src
)

# Also include wlroots system headers
target_include_directories(webcompositor PRIVATE
    ${WLROOTS_INCLUDE_DIRS}
    ${WAYLAND_SERVER_INCLUDE_DIRS}
)

# Link Qt libraries
target_link_libraries(webcompositor
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::WebEngineQuick
    Qt6::WebChannel
)

# Add WebEngine compile definition
target_compile_definitions(webcompositor PRIVATE
    QT_WEBENGINE_ENABLED
)

# Link pkg-config dependencies
target_link_libraries(webcompositor PRIVATE 
    PkgConfig::WLROOTS
    PkgConfig::WAYLAND_SERVER
    PkgConfig::PIXMAN
)

# Link waylib and qwlroots (submodule builds)
if(TARGET WaylibSharedServer)
    target_link_libraries(webcompositor PRIVATE WaylibSharedServer)
    message(STATUS "Linking against WaylibSharedServer")
elseif(TARGET Waylib::SharedServer)
    target_link_libraries(webcompositor PRIVATE Waylib::SharedServer)
    message(STATUS "Linking against Waylib::SharedServer")
else()
    message(FATAL_ERROR "No Waylib target found!")
endif()

if(TARGET qwlroots)
    target_link_libraries(webcompositor PRIVATE qwlroots)
    message(STATUS "Linking against qwlroots")
elseif(TARGET QWlroots::QWlroots)
    target_link_libraries(webcompositor PRIVATE QWlroots::QWlroots)
    message(STATUS "Linking against QWlroots::QWlroots")
else()
    message(FATAL_ERROR "No qwlroots target found!")
endif()
