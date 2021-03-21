cmake_minimum_required(VERSION 3.16.0)

project(navigation)

file(GLOB_RECURSE NAVIGATION_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${NAVIGATION_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${NAVIGATION_SRCS})

target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH")
target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite ${KBE_ROOT}/lib/dependencies/tmxparser/src)
target_link_libraries(${PROJECT_NAME} PRIVATE g3dlite tmxparser)

target_compile_definitions(${PROJECT_NAME}Static PRIVATE "-DUSE_G3DMATH")
target_include_directories(${PROJECT_NAME}Static PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite ${KBE_ROOT}/lib/dependencies/tmxparser/src)
target_link_libraries(${PROJECT_NAME}Static PRIVATE g3dlite tmxparser)