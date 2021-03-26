cmake_minimum_required(VERSION 3.16.0)

project(bots)

file(GLOB_RECURSE BOTS_SRCS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${BOTS_SRCS})

# link lib libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXECUTABLE_LINK_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DKBE_BOTS")

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)