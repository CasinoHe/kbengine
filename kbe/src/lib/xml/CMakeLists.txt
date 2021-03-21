cmake_minimum_required(VERSION 3.16.0)

project(xml)

file(GLOB_RECURSE XML_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${XML_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${XML_SRCS})