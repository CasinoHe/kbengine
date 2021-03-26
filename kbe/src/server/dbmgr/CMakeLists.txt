cmake_minimum_required(VERSION 3.16.0)

project(dbmgr)

file(GLOB_RECURSE DBMGR_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${DBMGR_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_REDIS -DKBE_DBMGR")