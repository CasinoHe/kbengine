cmake_minimum_required(VERSION 3.16.0)

project(loginapp)

file(GLOB_RECURSE LOGINAPP_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${LOGINAPP_SRCS})
 
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES} Python::Python)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DKBE_LOGINAPP -DUSE_JWSMTP")