cmake_minimum_required(VERSION 3.16.0)

project(network)

file(GLOB_RECURSE NETWORK_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${NETWORK_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${NETWORK_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE ssl crypto dl)
target_link_libraries(${PROJECT_NAME}Static PRIVATE ssl crypto dl)