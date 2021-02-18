cmake_minimum_required(VERSION 3.16)
project("rlib-interation")

add_subdirectory(rlib)

option(RLIB_ENABLE_TESTING "Include testing subproject, requiring GTest/GMock availability" ON)

if (RLIB_ENABLE_TESTING)
  enable_testing()

  set(Boost_DEBUG 1)
  find_package(Boost REQUIRED)
  include_directories(${Boost_INCLUDE_DIRS})
  add_subdirectory(rlib-tests)
endif()
