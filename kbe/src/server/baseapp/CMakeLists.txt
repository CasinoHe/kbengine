cmake_minimum_required(VERSION 3.16.0)

project(baseapp)

file(GLOB_RECURSE BASEAPP_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${BASEAPP_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE server entitydef pyscript network common helper resmgr thread)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH")
target_link_libraries(${PROJECT_NAME} PRIVATE g3dlite ssl log4cxx python${PYTHON_VERSION} fmt tinyxml crypto pthread util dl)