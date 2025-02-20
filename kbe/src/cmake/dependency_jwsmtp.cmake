message(STATUS "Start compile thirdparty dependeny: jwsmtp")

ExternalProject_Add(jwsmtp
  PREFIX ${DEPENDENCIES_BUILD_DIR}/jwsmtp
  SOURCE_DIR ${DEPENDENCIES_DIR}/jwsmtp
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_INSTALL_DIR}
  TEST_COMMAND ""
)

set(JWSMTP_FOUND TRUE)
set(JWSMTP_INCLUDE_DIRS ${DEPENDENCIES_INSTALL_DIR}/include/jwsmtp)
set(JWSMTP_LIBRARY_DIRS ${DEPENDENCIES_INSTALL_DIR}/lib})
set(JWSMTP_LIBRARIES ${DEPENDENCIES_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}jwsmtp${CMAKE_SHARED_LIBRARY_SUFFIX})