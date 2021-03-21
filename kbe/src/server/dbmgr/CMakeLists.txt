cmake_minimum_required(VERSION 3.16.0)

project(dbmgr)

file(GLOB_RECURSE DBMGR_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${DBMGR_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/g3dlite)
# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE server network common pyscript entitydef resmgr helper thread)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DUSE_G3DMATH -DUSE_KBE_MYSQL -DUSE_REDIS -DKBE_DBMGR")
target_link_libraries(${PROJECT_NAME} PRIVATE g3dlite ssl log4cxx python${PYTHON_VERSION} db_interface db_redis db_mysql hiredis fmt tinyxml crypto pthread util dl)