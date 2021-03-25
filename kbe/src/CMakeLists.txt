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

set(LIB_SOURCE_DIR ${KBE_ROOT}/lib)
set(DEPENDENCIES_DIR ${LIB_SOURCE_DIR}/dependencies)
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
  dependency_expat
  dependency_log4cxx
  dependency_python
)

include(ExternalProject)
foreach (lib ${DEPENDENCIES_LIBRARIES})
  include(${lib})
endforeach()

# message(STATUS "LIB IS : ${ZLIB_LIBRARIES}, ${FMT_LIBRARIES}, ${JEMALLOC_LIBRARIES} ${CURL_LIBRARIES} ${G3DLITE_LIBRARIES}")
add_dependencies(tmxparser tinyxml zlib)
add_dependencies(aprutil apr)
add_dependencies(log4cxx apr aprutil)

set(DEPENDENCIES_INCLUDE_DIRECTORIS 
  ${ZLIB_INCLUDE_DIRS}
  ${FMT_INCLUDE_DIRS}
  ${JEMALLOC_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIRS}
  ${HIREDIS_INCLUDE_DIRS}
  ${G3DLITE_INCLUDE_DIRS}
  ${SIGAR_INCLUDE_DIRS}
  ${TINYXML_INCLUDE_DIRS}
  ${TMXPARSER_INCLUDE_DIRS}
  ${JWSMTP_INCLUDE_DIRS}
  ${APR_INCLUDE_DIRS}
  ${APR_UTIL_INCLUDE_DIRS}
  ${EXPAT_INCLUDE_DIRS}
  ${LOG4CXX_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS}
)
include_directories(${DEPENDENCIES_INCLUDE_DIRECTORIS} ${DEPENDENCIES_INSTALL_DIR}/include ${LIB_SOURCE_DIR} ${KBE_ROOT}/server ${DEPENDENCIES_DIR})

set(DEPENDENCIES_LIBRARIES
  ${ZLIB_LIBRARIES}
  ${FMT_LIBRARIES}  
  ${JEMALLOC_LIBRARIES}
  ${CURL_LIBRARIES}
  ${HIREDIS_LIBRARIES}
  ${G3DLITE_LIBRARIES}
  ${SIGAR_LIBRARIES}
  ${TINYXML_LIBRARIES}
  ${TMXPARSER_LIBRARIES}
  ${JWSMTP_LIBRARIES}
  ${APR_LIBRARIES}
  ${APR_UTIL_LIBRARIES}
  ${EXPAT_LIBRARIES}
  ${LOG4CXX_LIBRARIES}
  ${PYTHON_LIBRARIES}
)

option(ENABLE_WATCHERS "enable watchers, default is ON" ON)
option(USE_OPENSSL "enable openssl, default is ON" ON)
option(USE_G3DMATH "enable use g3dmath, default is ON" ON)
option(USE_SYSTEM_MYSQL "enable use system mysql" ON)

if (UNIX)
  if (USE_OPENSSL)
    set(LIBS_LINK_LIBRARIES ${DEPENDENCIES_LIBRARIES} crypto ssl pthread util dl)
  else()
    set(LIBS_LINK_LIBRARIES ${DEPENDENCIES_LIBRARIES} pthread util dl)
  endif()

  if (USE_SYSTEM_MYSQL)
    list(APPEND LIBS_LINK_LIBRARIES mariadb)
  endif()
else()
  set(LIBS_LINK_LIBRARIES ${DEPENDENCIES_LIBRARIES})
endif()

add_subdirectory(lib)
# add_subdirectory(server)