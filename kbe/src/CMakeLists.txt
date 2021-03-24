cmake_minimum_required(VERSION 3.16.0)

project(kbengine)

set(KBE_ROOT ${CMAKE_SOURCE_DIR})

# export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CXX standard
set(CMAKE_CXX_STANDARD 17)

# do not set rpath
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_SKIP_INSTALL_RPATH TRUE)

# global definitions
set(PYTHON_LIBRARIES "")
set(PYTHON_VERSION 3.9)

set(DEPENDENCIES_DIR ${KBE_ROOT}/lib/dependencies)
set(DEPENDENCIES_INSTALL_DIR ${CMAKE_BINARY_DIR}/dependencies)
set(DEPENDENCIES_BUILD_DIR ${CMAKE_BINARY_DIR}/lib/dependencies)

if (NOT EXISTS ${DEPENDENCIES_INSTALL_DIR})
  file(MAKE_DIRECTORY ${DEPENDENCIES_INSTALL_DIR})
endif()
if (NOT EXISTS ${DEPENDENCIES_BUILD_DIR})
  file(MAKE_DIRECTORY ${DEPENDENCIES_BUILD_DIR})
endif()

list(APPEND CMAKE_MODULE_PATH ${KBE_ROOT}/cmake)

set(DEPENDENCIES_LIBRARIES
  dependency_zlib
  dependency_fmt
  dependency_jemalloc
  dependency_curl
  dependency_hiredis
  dependency_g3dlite
  dependency_sigar
  dependency_tinyxml
  dependency_tmxparser
  dependency_jwsmtp
  dependency_apr
  dependency_aprutil
)

include(ExternalProject)
foreach (lib ${DEPENDENCIES_LIBRARIES})
  include(${lib})
endforeach()

# add_subdirectory(lib)
# add_subdirectory(server)

message(STATUS "LIB IS : ${ZLIB_LIBRARIES}, ${FMT_LIBRARIES}, ${JEMALLOC_LIBRARIES} ${CURL_LIBRARIES} ${G3DLITE_LIBRARIES}")
add_dependencies(tmxparser tinyxml zlib)
add_dependencies(aprutil apr)