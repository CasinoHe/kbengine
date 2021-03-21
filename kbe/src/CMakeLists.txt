cmake_minimum_required(VERSION 3.16.0)

project(kbengine)

set(KBE_ROOT ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(PYTHON_LIBRARIES "")
set(PYTHON_VERSION 3.9)

add_subdirectory(lib)
add_subdirectory(server)