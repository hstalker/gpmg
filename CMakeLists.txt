################################################################################
# Shin #########################################################################
cmake_minimum_required(VERSION 2.8.0)
project(gpmg-cxx CXX)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


# Version ######################################################################
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 0 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 1 CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)


# Install paths ################################################################
set(EXEC_INSTALL_PREFIX "${PROJECT_INSTALL_PREFIX}"
  CACHE PATH "Base installation path for executables."
)
set(BIN_INSTALL_DIR "${EXEC_INSTALL_PREFIX}/bin"
  CACHE PATH "Installation directory for binaries (default: prefix/bin)."
)
set(LIB_INSTALL_DIR "${EXEC_INSTALL_PREFIX}/lib"
  CACHE PATH "Installation directory for libraries (default: prefix/lib)."
)
set(INCLUDE_INSTALL_DIR "${EXEC_INSTALL_PREFIX}/include"
  CACHE PATH "Installation directory for header files (default: prefix/include)."
)


# Options ######################################################################
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTS "Build test programs" ON)
option(BUILD_DOCS "Build documentation (requires doxygen)" OFF)


# Compiler setup ###############################################################
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -fstrict-aliasing -fno-rtti -fno-exceptions -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -fstrict-aliasing -fno-rtti -fno-exceptions -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /W4 /GR- /EHsc")
else ()
    message(STATUS "This compiler currently unsupported! Attempting to continue anyway...")
endif ()

# Recurse subdirectories #######################################################
if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)

if (BUILD_DOCS)
    add_subdirectory(docs)
endif (BUILD_DOCS)

