cmake_minimum_required(VERSION 3.16.0)

project(kbengine)

set(KBE_ROOT ${CMAKE_SOURCE_DIR})

# export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CXX standard
set(CMAKE_CXX_STANDARD 17)

# do not set rpath
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_SKIP_INSTALL_RPATH TRUE)

# # global definitions
# set(PYTHON_LIBRARIES "")
# set(PYTHON_VERSION 3.9)

set(LIB_SOURCE_DIR ${KBE_ROOT}/lib)
set(DEPENDENCIES_DIR ${LIB_SOURCE_DIR}/dependencies)
set(DEPENDENCIES_INSTALL_DIR ${CMAKE_BINARY_DIR}/dependencies)
set(DEPENDENCIES_BUILD_DIR ${CMAKE_BINARY_DIR}/lib/dependencies)

if (NOT EXISTS ${DEPENDENCIES_INSTALL_DIR})
  file(MAKE_DIRECTORY ${DEPENDENCIES_INSTALL_DIR})
endif()
if (NOT EXISTS ${DEPENDENCIES_BUILD_DIR})
  file(MAKE_DIRECTORY ${DEPENDENCIES_BUILD_DIR})
endif()

list(APPEND CMAKE_MODULE_PATH ${KBE_ROOT}/cmake)

set(DEPENDENCIES_EXTERNAL_LIBRARIES
  dependency_zlib
  dependency_fmt
  dependency_jemalloc
  dependency_curl
  dependency_hiredis
  dependency_g3dlite
  dependency_sigar
  dependency_tinyxml
  dependency_tmxparser
  dependency_jwsmtp
  dependency_apr
  dependency_aprutil
  dependency_expat
  dependency_log4cxx
  # dependency_python
)

include(ExternalProject)
foreach (lib ${DEPENDENCIES_EXTERNAL_LIBRARIES})
  include(${lib})
endforeach()

find_package(Python REQUIRED COMPONENTS Development)

# message(STATUS "LIB IS : ${ZLIB_LIBRARIES}, ${FMT_LIBRARIES}, ${JEMALLOC_LIBRARIES} ${CURL_LIBRARIES} ${G3DLITE_LIBRARIES}")
add_dependencies(tmxparser tinyxml zlib)
add_dependencies(aprutil apr)
add_dependencies(log4cxx apr aprutil)

set(DEPENDENCIES_INCLUDE_DIRECTORIS 
  ${ZLIB_INCLUDE_DIRS}
  ${FMT_INCLUDE_DIRS}
  ${JEMALLOC_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIRS}
  ${HIREDIS_INCLUDE_DIRS}
  ${G3DLITE_INCLUDE_DIRS}
  ${SIGAR_INCLUDE_DIRS}
  ${TINYXML_INCLUDE_DIRS}
  ${TMXPARSER_INCLUDE_DIRS}
  ${JWSMTP_INCLUDE_DIRS}
  ${APR_INCLUDE_DIRS}
  ${APR_UTIL_INCLUDE_DIRS}
  ${EXPAT_INCLUDE_DIRS}
  ${LOG4CXX_INCLUDE_DIRS}
  ${Python_INCLUDE_DIRS}
)
include_directories(${DEPENDENCIES_INCLUDE_DIRECTORIS} ${DEPENDENCIES_INSTALL_DIR}/include ${LIB_SOURCE_DIR} ${KBE_ROOT}/server ${DEPENDENCIES_DIR})

set(DEPENDENCIES_LIBRARIES
  ${ZLIB_LIBRARIES}
  ${FMT_LIBRARIES}  
  ${JEMALLOC_LIBRARIES}
  ${CURL_LIBRARIES}
  ${HIREDIS_LIBRARIES}
  ${G3DLITE_LIBRARIES}
  ${SIGAR_LIBRARIES}
  ${TINYXML_LIBRARIES}
  ${TMXPARSER_LIBRARIES}
  ${JWSMTP_LIBRARIES}
  ${APR_LIBRARIES}
  ${APR_UTIL_LIBRARIES}
  ${EXPAT_LIBRARIES}
  ${LOG4CXX_LIBRARIES}
)

# touch all lib files, so the dependencies is OK
if (NOT EXISTS ${DEPENDENCIES_INSTALL_DIR}/lib)
  file(MAKE_DIRECTORY ${DEPENDENCIES_INSTALL_DIR}/lib)
endif()
file(TOUCH ${DEPENDENCIES_LIBRARIES})
list(APPEND ${DEPENDENCIES_LIBRARIES} Python::Python)

option(ENABLE_WATCHERS "enable watchers, default is ON" ON)
option(USE_OPENSSL "enable openssl, default is ON" ON)
option(USE_G3DMATH "enable use g3dmath, default is ON" ON)
option(USE_SYSTEM_MYSQL "enable use system mysql" ON)

if (UNIX)
  if (USE_OPENSSL)
    set(LIBS_LINK_LIBRARIES ${DEPENDENCIES_LIBRARIES} crypto ssl pthread util dl)
  else()
    set(LIBS_LINK_LIBRARIES ${DEPENDENCIES_LIBRARIES} pthread util dl)
  endif()

  if (USE_SYSTEM_MYSQL)
    list(APPEND LIBS_LINK_LIBRARIES mysqlclient m rt resolv)
  endif()
else()
  set(LIBS_LINK_LIBRARIES ${DEPENDENCIES_LIBRARIES})
endif()

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

add_subdirectory(lib)

set(EXECUTABLE_LINK_LIBRARIES 
  server
  client_lib 
  common 
  db_redis 
  db_mysql 
  db_interface 
  entitydef
  math
  resmgr
  pyscript
  network
  helper
  thread
  navigation
  xml
  ${LIBS_LINK_LIBRARIES}
)

add_subdirectory(server)

# add lib dependencies
add_dependencies(client_lib zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(common zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(db_redis zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(db_mysql zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(db_interface db_mysql db_redis zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(entitydef client_lib zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(math zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(resmgr zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(pyscript zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(server zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(network zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(helper zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(thread zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(xml zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(navigation zlib fmt jemalloc curl hiredis g3dlite sigar tinyxml tmxparser jwsmtp apr aprutil expat log4cxx)
add_dependencies(server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)

# add executable dependencies
add_dependencies(baseapp server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(baseappmgr server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(cellapp server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread navigation xml)
add_dependencies(cellappmgr server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread navigation xml)
add_dependencies(dbmgr server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(loginapp server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(machine server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
# tools dependencies
add_dependencies(bots server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(interfaces server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(logger server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
add_dependencies(kbcmd server client_lib common db_redis db_mysql db_interface entitydef math resmgr pyscript network helper thread xml)
