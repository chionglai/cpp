
# Replace all fields <...>:
# 1. lib_name: Name for the library.
# 2. lib_desc: Description for the library.
# 3. version_no: Version number
# 4. list_of_public_headers: List of all public headers to be copied
#    to installed directory.
set(LIB_NAME lcc)
set(LIB_DESC "LCC C++ libraries")
set(LIB_VER 0.0.1)
set(EXTRA_COMPILE_FLAG "-std=c++11")
file(GLOB PUBLIC_HEADER_FILES inc/*.h)

# END setup - Do not modify pass this line

set(LIB_STATIC ${LIB_NAME}_static)
set(LIB_SHARED ${LIB_NAME}_shared)

# Required cmake min version
cmake_minimum_required(VERSION 3.9)

# Project info
project(${LIB_NAME} VERSION ${LIB_VER} DESCRIPTION ${LIB_DESC})

# Set additional compile flag for both C and C++
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILE_FLAG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAG}")

# Change default install prefix
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX install CACHE PATH "No comment" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Add source
file(GLOB SOURCES src/*.cpp)
add_library(objsrc OBJECT ${SOURCES})

# Declare target static library
add_library(${LIB_STATIC} STATIC $<TARGET_OBJECTS:objsrc>)

# Set properties for static library
set_target_properties(${LIB_STATIC} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib  # Output of compiled library
    PUBLIC_HEADER "${PUBLIC_HEADER_FILES}"              # List of public header files
    VERSION ${PROJECT_VERSION}                          # Version number
)

# Declare target shared library
add_library(${LIB_SHARED} SHARED $<TARGET_OBJECTS:objsrc>)

# Set properties for shared library
set_target_properties(${LIB_SHARED} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
    PUBLIC_HEADER "${PUBLIC_HEADER_FILES}"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Include top directory for compilation
#target_include_directories(objsrc PRIVATE .)
target_include_directories(objsrc PRIVATE inc)
target_include_directories(objsrc PRIVATE src)

# Include GNUInstallDirs to use variables CMAKE_INSTALL*DIR
include(GNUInstallDirs)

install(TARGETS ${LIB_STATIC}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Declare files to install for shared library
install(TARGETS ${LIB_SHARED}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Add rule to expand @ macros only
configure_file(${LIB_NAME}.pc.in ${LIB_NAME}.pc @ONLY)

# Install generated file
install(FILES ${CMAKE_BINARY_DIR}/${LIB_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
