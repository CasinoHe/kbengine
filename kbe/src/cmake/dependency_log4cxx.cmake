message(STATUS "Start compile thirdparty dependeny: log4cxx")

ExternalProject_Add(log4cxx
  PREFIX ${DEPENDENCIES_BUILD_DIR}/log4cxx
  SOURCE_DIR ${DEPENDENCIES_DIR}/log4cxx
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_INSTALL_DIR}
             -DAPR_CONFIG_EXECUTABLE=${DEPENDENCIES_INSTALL_DIR}/dependencies/bin/apr-1-config
             -DAPR_UTIL_CONFIG_EXECUTABLE=${DEPENDENCIES_INSTALL_DIR}/dependencies/bin/apu-1-config
             -DAPR_INCLUDE_DIR=${APR_INCLUDE_DIRS}
             -DAPR_UTIL_INCLUDE_DIR=${APRUTIL_INCLUDE_DIRS}
             -DAPR_LIBRARIES=${APR_LIBRARIES}
             -DAPR_UTIL_LIBRARIES=${APRUTIL_LIBRARIES}
             -DBUILD_TESTING=OFF
  TEST_COMMAND ""
)

set(LOG4CXX_FOUND TRUE)
set(LOG4CXX_INCLUDE_DIRS ${DEPENDENCIES_INSTALL_DIR}/include)
set(LOG4CXX_LIBRARY_DIRS ${DEPENDENCIES_INSTALL_DIR}/lib})
set(LOG4CXX_LIBRARIES ${DEPENDENCIES_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}log4cxx${CMAKE_SHARED_LIBRARY_SUFFIX})