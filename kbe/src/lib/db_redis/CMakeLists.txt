cmake_minimum_required(VERSION 3.16.0)

project(db_redis)

file(GLOB_RECURSE DB_REDIS_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${DB_REDIS_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${DB_REDIS_SRCS})

target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH")
target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/hiredis)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread util dl g3dlite)


target_compile_definitions(${PROJECT_NAME}Static PRIVATE "-DUSE_G3DMATH")
target_include_directories(${PROJECT_NAME}Static PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
target_include_directories(${PROJECT_NAME}Static PRIVATE ${KBE_ROOT}/lib/dependencies/hiredis)
target_link_libraries(${PROJECT_NAME}Static PRIVATE pthread util dl g3dlite)