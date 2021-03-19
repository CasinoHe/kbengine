cmake_minimum_required(VERSION 3.16.0)

project(pyscript)

file(GLOB_RECURSE PYSCRIPT_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${PYSCRIPT_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${PYSCRIPT_SRCS})

target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH")
target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
target_link_libraries(${PROJECT_NAME} PRIVATE g3dlite pthread util dl)

target_compile_definitions(${PROJECT_NAME}Static PRIVATE "-DUSE_G3DMATH")
target_include_directories(${PROJECT_NAME}Static PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
target_link_libraries(${PROJECT_NAME}Static PRIVATE g3dlite pthread util dl)