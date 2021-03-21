cmake_minimum_required(VERSION 3.16.0)

project(thread)

file(GLOB_RECURSE THREAD_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${THREAD_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${THREAD_SRCS})