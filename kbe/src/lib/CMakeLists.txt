cmake_minimum_required(VERSION 3.16.0)

# compile kbengine libs
if (ENABLE_WATCHERS)
  add_definitions("-DENABLE_WATCHERS")
endif()

if (USE_OPENSSL)
  add_definitions("-DUSE_OPENSSL")
endif()

if (USE_G3DMATH)
  add_definitions("-DUSE_G3DMATH")
endif()

if (USE_SYSTEM_MYSQL)
  include_directories(/usr/include/mariadb/server)
endif()

add_subdirectory(client_lib)
add_subdirectory(common)
add_subdirectory(db_redis)
add_subdirectory(db_mysql)
add_subdirectory(db_interface)
add_subdirectory(entitydef)
add_subdirectory(math)
add_subdirectory(resmgr)
add_subdirectory(pyscript)
add_subdirectory(server)
add_subdirectory(navigation)
add_subdirectory(network)
add_subdirectory(helper)
add_subdirectory(thread)
add_subdirectory(xml)