cmake_minimum_required(VERSION 3.16.0)

project(client_lib)

file(GLOB_RECURSE CLIENT_LIB_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${CLIENT_LIB_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${CLIENT_LIB_SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${KBE_ROOT}/lib/dependencies/g3dlite)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib/dependencies/log4cxx/src/main/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${KBE_ROOT}/lib/dependencies/log4cxx/src/main/include)
target_link_libraries(${PROJECT_NAME} ssl crypto pthread util dl)

target_include_directories(${PROJECT_NAME}Static PUBLIC ${KBE_ROOT}/lib/dependencies/g3dlite)
target_include_directories(${PROJECT_NAME}Static PUBLIC ${CMAKE_BINARY_DIR}/lib/dependencies/log4cxx/src/main/include)
target_include_directories(${PROJECT_NAME}Static PUBLIC ${KBE_ROOT}/lib/dependencies/log4cxx/src/main/include)
target_link_libraries(${PROJECT_NAME}Static ssl crypto pthread util dl)