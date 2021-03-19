cmake_minimum_required(VERSION 3.16.0)

project(common)

file(GLOB_RECURSE COMMON_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${COMMON_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${COMMON_SRCS})