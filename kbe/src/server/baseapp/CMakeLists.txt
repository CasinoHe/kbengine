cmake_minimum_required(VERSION 3.16.0)

project(baseapp)

file(GLOB_RECURSE BASEAPP_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${BASEAPP_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES})