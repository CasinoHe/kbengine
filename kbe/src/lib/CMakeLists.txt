cmake_minimum_required(VERSION 3.16.0)

include(ExternalProject)

add_subdirectory(dependencies/zlib)
set(ZLIB_LIBRARIES zlib)

add_subdirectory(dependencies/fmt)

# use autogen to build jemalloc
ExternalProject_Add(jemalloc
  PREFIX ${KBE_ROOT}/lib/dependencies/jemalloc
  SOURCE_DIR ${KBE_ROOT}/lib/dependencies/jemalloc
  CONFIGURE_COMMAND ./autogen.sh
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${KBE_ROOT}/lib/dependencies/jemalloc/lib ${CMAKE_BINARY_DIR}/lib/dependencies/jemalloc
)

add_subdirectory(dependencies/curl)
add_subdirectory(dependencies/hiredis)
add_subdirectory(dependencies/g3dlite)
add_subdirectory(dependencies/tinyxml)
set(TINYXML_LIBRARIES tinyxml)

add_subdirectory(dependencies/sigar)

include_directories(dependencies/tinyxml)
add_subdirectory(dependencies/tmxparser)
add_subdirectory(dependencies/jwsmtp)
add_subdirectory(dependencies/apr)