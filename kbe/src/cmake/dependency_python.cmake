message(STATUS "Start compile thirdparty dependeny: python")

ExternalProject_Add(python
  PREFIX ${DEPENDENCIES_BUILD_DIR}/python
  SOURCE_DIR ${LIB_SOURCE_DIR}/python
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CONFIGURE_COMMAND git clean -df COMMAND ./configure --prefix=${DEPENDENCIES_INSTALL_DIR} --enable-optimizations --enable-shared --with-suffix=3
  BUILD_COMMAND make clean COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
  TEST_COMMAND ""
)

set(PYTHON_FOUND TRUE)
set(PYTHON_INCLUDE_DIRS ${DEPENDENCIES_INSTALL_DIR}/include/python3.9)
set(PYTHON_LIBRARY_DIRS ${DEPENDENCIES_INSTALL_DIR}/lib})
set(PYTHON_LIBRARIES ${DEPENDENCIES_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}python3${CMAKE_SHARED_LIBRARY_SUFFIX})