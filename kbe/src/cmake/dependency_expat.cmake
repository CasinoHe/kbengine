message(STATUS "Start compile thirdparty dependeny: expat")

ExternalProject_Add(expat
  PREFIX ${DEPENDENCIES_BUILD_DIR}/expat
  SOURCE_DIR ${DEPENDENCIES_DIR}/expat/expat
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_INSTALL_DIR}
             -DEXPAT_BUILD_EXAMPLES=OFF
             -DEXPAT_BUILD_TESTS=OFF
             -DEXPAT_BUILD_DOCS=OFF
  TEST_COMMAND ""
)

set(EXPAT_FOUND TRUE)
set(EXPAT_INCLUDE_DIRS ${DEPENDENCIES_INSTALL_DIR}/include)
set(EXPAT_LIBRARY_DIRS ${DEPENDENCIES_INSTALL_DIR}/lib})
set(EXPAT_LIBRARIES ${DEPENDENCIES_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}expat${CMAKE_SHARED_LIBRARY_SUFFIX})