cmake_minimum_required(VERSION 3.16.0)

project(machine)

file(GLOB_RECURSE MACHINE_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${MACHINE_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE server network common resmgr pyscript entitydef client_lib helper thread)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH -DKBE_MACHINE -DLOG4CXX_STATIC")
target_link_libraries(${PROJECT_NAME} PRIVATE g3dlite ssl log4cxx python${PYTHON_VERSION} tinyxml fmt crypto pthread util dl)