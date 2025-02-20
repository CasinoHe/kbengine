message(STATUS "Start compile thirdparty dependeny: curl")

ExternalProject_Add(curl
  PREFIX ${DEPENDENCIES_BUILD_DIR}/curl
  SOURCE_DIR ${DEPENDENCIES_DIR}/curl
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_INSTALL_DIR}
             -DBUILD_CURL_EXE=OFF
  TEST_COMMAND ""
)

set(CURL_FOUND TRUE)
set(CURL_INCLUDE_DIRS ${DEPENDENCIES_INSTALL_DIR}/include)
set(CURL_LIBRARY_DIRS ${DEPENDENCIES_INSTALL_DIR}/lib})
set(CURL_LIBRARIES ${DEPENDENCIES_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}curl-d${CMAKE_SHARED_LIBRARY_SUFFIX} ${DEPENDENCIES_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}curl${CMAKE_SHARED_LIBRARY_SUFFIX})