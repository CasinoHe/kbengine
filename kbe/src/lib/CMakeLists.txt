cmake_minimum_required(VERSION 3.16.0)

include(ExternalProject)

# ------------------------------------------ build all thirdparty dependencies start --------------------------------------------------------------------
add_subdirectory(dependencies/zlib)
set(ZLIB_LIBRARIES zlib)

add_subdirectory(dependencies/fmt)

# use autogen to build jemalloc
ExternalProject_Add(jemalloc
  PREFIX ${KBE_ROOT}/lib/dependencies/jemalloc
  SOURCE_DIR ${KBE_ROOT}/lib/dependencies/jemalloc
  CONFIGURE_COMMAND ./autogen.sh --prefix=${CMAKE_BINARY_DIR}/lib/dependencies/jemalloc
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  # INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${KBE_ROOT}/lib/dependencies/jemalloc/lib ${CMAKE_BINARY_DIR}/lib/dependencies/jemalloc
  INSTALL_COMMAND make install
)
include_directories(${CMAKE_BINARY_DIR}/lib/dependencies/jemalloc/include)
link_directories(${CMAKE_BINARY_DIR}/lib/dependencies/jemalloc/lib)

add_subdirectory(dependencies/curl)
add_subdirectory(dependencies/hiredis)
add_subdirectory(dependencies/g3dlite)
add_subdirectory(dependencies/tinyxml)
set(TINYXML_LIBRARIES tinyxml)

add_subdirectory(dependencies/sigar)

include_directories(dependencies/tinyxml)
add_subdirectory(dependencies/tmxparser)
add_subdirectory(dependencies/jwsmtp)

if (WIN32)
  add_subdirectory(dependencies/apr)
else()
  ExternalProject_Add(apr
    PREFIX ${KBE_ROOT}/lib/dependencies/apr
    SOURCE_DIR ${KBE_ROOT}/lib/dependencies/apr
    CONFIGURE_COMMAND ./buildconf COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}/lib/dependencies/apr
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND make install
  )
  include_directories(${CMAKE_BINARY_DIR}/lib/dependencies/apr/include/apr-1)
  link_directories(${CMAKE_BINARY_DIR}/lib/dependencies/apr/lib)
  set(APR_INCLUDE_DIR ${CMAKE_BINARY_DIR}/lib/dependencies/apr/include)
  set(APR_LIBRARIES apr-1)
  set(APR_CONFIG_EXECUTABLE ${CMAKE_BINARY_DIR}/lib/dependencies/apr/bin/apr-1-config)
endif()

add_subdirectory(dependencies/expat/expat)

if (WIN32)
  add_subdirectory(dependencies/apr-util)
else()
  ExternalProject_Add(apr-uril
    PREFIX ${KBE_ROOT}/lib/dependencies/apr-util
    SOURCE_DIR ${KBE_ROOT}/lib/dependencies/apr-util
    CONFIGURE_COMMAND ./buildconf COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}/lib/dependencies/apr-util -with-apr=${CMAKE_BINARY_DIR}/lib/dependencies/apr
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND make install
  )
  include_directories(${CMAKE_BINARY_DIR}/lib/dependencies/apr-util/include/apr-1)
  link_directories(${CMAKE_BINARY_DIR}/lib/dependencies/apr-util/lib)
  set(APR_UTIL_INCLUDE_DIR ${CMAKE_BINARY_DIR}/lib/dependencies/apr-util/include/apr-1)
  set(APR_UTIL_LIBRARIES aprutil-1)
endif()

add_subdirectory(dependencies/log4cxx)

ExternalProject_Add(python
  PREFIX ${KBE_ROOT}/lib/python
  SOURCE_DIR ${KBE_ROOT}/lib/python
  CONFIGURE_COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}/lib/python --enable-optimizations
  BUILD_COMMAND make clean COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
)

# ------------------------------------------ build all thirdparty dependencies finished --------------------------------------------------------------------

# common include directory
include_directories(${KBE_ROOT})
include_directories(${KBE_ROOT}/lib)
include_directories(${KBE_ROOT}/server)
include_directories(${KBE_ROOT}/lib/dependencies)
include_directories(${KBE_ROOT}/lib/dependencies/zlib)
include_directories(${KBE_ROOT}/lib/dependencies/tinyxml)
include_directories(${KBE_ROOT}/lib/dependencies/fmt/include)
include_directories(${KBE_ROOT}/lib/dependencies/curl/include)
include_directories(${KBE_ROOT}/lib/dependencies/log4cxx/src/main/include)
include_directories(${CMAKE_BINARY_DIR}/lib/python/include/python3.9)
include_directories(${CMAKE_BINARY_DIR}/lib/dependencies/log4cxx/src/main/include)

# compile kbengine libs
add_definitions("-DENABLE_WATCHERS")
add_definitions("-DUSE_OPENSSL")
add_subdirectory(client_lib)
add_subdirectory(common)
add_subdirectory(db_redis)
add_subdirectory(db_mysql)
add_subdirectory(db_interface)
add_subdirectory(entitydef)
add_subdirectory(math)
add_subdirectory(resmgr)
add_subdirectory(pyscript)
add_subdirectory(server)
add_subdirectory(navigation)
add_subdirectory(network)
add_subdirectory(helper)