cmake_minimum_required(VERSION 3.16.0)

project(kbcmd)

file(GLOB_RECURSE KBCMD_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${KBCMD_SRCS})

# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES} Python::Python)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DKBE_LOGGER")