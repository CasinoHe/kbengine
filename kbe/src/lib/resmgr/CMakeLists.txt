cmake_minimum_required(VERSION 3.16.0)

project(resmgr)

file(GLOB_RECURSE RESMGR_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${RESMGR_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${RESMGR_SRCS})