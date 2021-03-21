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
add_library(${PROJECT_NAME}Static STATIC ${HELPER_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE log4cxx)
target_include_directories(${PROJECT_NAME} PRIVATE ${KBE_ROOT}/lib/dependencies/sigar/include)

target_link_libraries(${PROJECT_NAME}Static PRIVATE log4cxx)
target_include_directories(${PROJECT_NAME}Static PRIVATE ${KBE_ROOT}/lib/dependencies/sigar/include)