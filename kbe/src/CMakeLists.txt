cmake_minimum_required(VERSION 3.16.0)

project(kbengine)

set(KBE_ROOT ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)