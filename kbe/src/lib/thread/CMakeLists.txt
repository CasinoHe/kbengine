cmake_minimum_required(VERSION 3.16.0)

project(thread)

file(GLOB_RECURSE THREAD_SRCS "*.h" "*.cpp")

add_library(${PROJECT_NAME} SHARED ${THREAD_SRCS})
add_library(${PROJECT_NAME}Static STATIC ${THREAD_SRCS})

# target_link_libraries(${PROJECT_NAME} PRIVATE log4cxx)
# target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/sigar/include)

# target_link_libraries(${PROJECT_NAME}Static PRIVATE log4cxx)
# target_include_directories(${PROJECT_NAME}Static PRIVATE ${KBE_ROOT}/lib/dependencies/sigar/include)