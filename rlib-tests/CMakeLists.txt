cmake_minimum_required(VERSION 3.16)
project(rlib-tests)

add_subdirectory(googletest)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS bitconverter/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} rlib)
target_link_libraries(${PROJECT_NAME} gmock_main)
