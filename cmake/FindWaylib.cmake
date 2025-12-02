# FindWaylib.cmake - Find Waylib library
#
# This module defines:
#  Waylib_FOUND - System has Waylib
#  Waylib_INCLUDE_DIRS - Waylib include directories
#  Waylib_LIBRARIES - Libraries needed to use Waylib
#
# Note: When using waylib-shared as a submodule with add_subdirectory(),
# this find module is not needed. The Waylib::SharedServer target will
# be automatically available.

find_path(Waylib_INCLUDE_DIR
    NAMES wserver.h
    PATH_SUFFIXES waylib/server
)

find_library(Waylib_LIBRARY
    NAMES Waylib SharedServer
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Waylib
    REQUIRED_VARS Waylib_LIBRARY Waylib_INCLUDE_DIR
)

if(Waylib_FOUND AND NOT TARGET Waylib::SharedServer)
    add_library(Waylib::SharedServer UNKNOWN IMPORTED)
    set_target_properties(Waylib::SharedServer PROPERTIES
        IMPORTED_LOCATION "${Waylib_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Waylib_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(Waylib_INCLUDE_DIR Waylib_LIBRARY)
