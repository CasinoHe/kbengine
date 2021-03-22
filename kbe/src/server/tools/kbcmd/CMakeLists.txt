cmake_minimum_required(VERSION 3.16.0)

project(kbcmd)

file(GLOB_RECURSE KBCMD_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${KBCMD_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE server network common resmgr pyscript entitydef client_lib helper thread)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH -DKBE_LOGGER")
target_link_libraries(${PROJECT_NAME} PRIVATE g3dlite ssl log4cxx python${PYTHON_VERSION} tinyxml fmt crypto pthread util dl)