project(rlib-tests)

set(INSTALL_GTEST OFF CACHE BOOL "")
add_subdirectory(googletest)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} rlib)
target_link_libraries(${PROJECT_NAME} gmock_main)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
