cmake_minimum_required(VERSION 3.16.0)

project(kbengine)

set(KBE_ROOT ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

# global definitions
set(PYTHON_LIBRARIES "")
set(PYTHON_VERSION 3.9)

set(OUTPUT_ROOT_DIR} ${CMAKE_BINARY_DIR}/output)
set(OUTPUT_LIB_DIR ${OUTPUT_ROOT_DIR}/lib)
set(OUTPUT_BIN_DIR ${OUTPUT_ROOT_DIR}/bin)

set(CMAKE_INSTALL_PREFIX ${OUTPUT_ROOT_DIR} CACHE STRING "cmake install prefix, default value ${OUTPUT_ROOT_DIR}")
set(CMAKE_INSTALL_LIBDIR ${OUTPUT_LIB_DIR} CACHE STRING "cmake install lib directory, default: ${OUTPUT_LIB_DIR}")
set(CMAKE_INSTALL_BINDIR ${OUTPUT_BIN_DIR} CACHE STRING "cmake install bin directory, default: ${OUTPUT_BIN_DIR}")

add_subdirectory(lib)
add_subdirectory(server)