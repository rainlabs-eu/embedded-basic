cmake_minimum_required(VERSION 3.16)
project("rlib-interation")

add_subdirectory(rlib)

enable_testing()

set(Boost_DEBUG 1)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_subdirectory(rlib-tests)
