cmake_minimum_required(VERSION 3.16.0)

project(cellappmgr)

file(GLOB_RECURSE CELLAPPMGR_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${CELLAPPMGR_SRCS})
 
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES} Python::Python)
# link lib libraries
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_TMXPARSER")
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DKBE_CELLAPPMGR")