cmake_minimum_required(VERSION 3.16.0)

project(baseappmgr)

file(GLOB_RECURSE BASEAPPMGR_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${BASEAPPMGR_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES} Python::Python)