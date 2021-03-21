cmake_minimum_required(VERSION 3.16.0)

include_directories(${KBE_ROOT}/lib)
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

add_definitions("-DENABLE_WATCHERS")
add_definitions("-DUSE_OPENSSL")

link_directories(${CMAKE_BINARY_DIR}/lib/python/lib)

add_subdirectory(baseapp)
add_subdirectory(baseappmgr)
add_subdirectory(cellapp)