cmake_minimum_required(VERSION 3.16.0)

project(helper)

file(GLOB_RECURSE HELPER_SRCS "*.h" "*.cpp")

if (UNIX)
  set(HELPER_FILT_SRCS "")
  foreach(SINGLE_SRC ${HELPER_SRCS})
    string(FIND ${SINGLE_SRC} crashhandler FIND_POS)
    if (${FIND_POS} EQUAL -1)
      list(APPEND HELPER_FILT_SRCS ${SINGLE_SRC})
    endif()
  endforeach()
  set(HELPER_SRCS ${HELPER_FILT_SRCS})
  list(REMOVE_ITEM HELPER_SRCS ./crashhandler.h ./crashhandler.cpp)
endif()


add_library(${PROJECT_NAME} SHARED ${HELPER_SRCS})
target_link_libraries(${PROJECT_NAME} ${LIBS_LINK_LIBRARIES})

# install headers
if (NOT EXISTS ${CMAKE_INSTALL_PREFIX}/include)
  file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
endif()

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)