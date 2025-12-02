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
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/waylib-shared/waylib/CMakeLists.txt")
        set(WITH_SUBMODULE_QWLROOTS ON)
        add_subdirectory(external/waylib-shared/waylib)
    else()
        message(WARNING "waylib-shared submodule not initialized. Run 'git submodule update --init --recursive'")
        set(WITH_SUBMODULE_WAYLIB OFF)
    endif()
endif()

# Add source directory
add_subdirectory(src)
