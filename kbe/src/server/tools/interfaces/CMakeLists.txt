cmake_minimum_required(VERSION 3.16.0)

project(interfaces)

file(GLOB_RECURSE INTERFACES_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${INTERFACES_SRCS})

# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DKBE_INTERFACES")