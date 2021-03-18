cmake_minimum_required(VERSION 3.16.0)

include(ExternalProject)

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
  include_directories(${CMAKE_BINARY_DIR}/lib/dependencies/apr/include)
  link_directories(${CMAKE_BINARY_DIR}/lib/dependencies/apr/lib)
endif()

add_subdirectory(dependencies/expat/expat)