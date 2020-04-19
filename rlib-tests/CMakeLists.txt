project(rlib-tests)
enable_testing()

set(INSTALL_GTEST OFF CACHE BOOL "")
add_subdirectory(googletest)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS bitconverter/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} rlib)
target_link_libraries(${PROJECT_NAME} gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})