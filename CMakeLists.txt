cmake_minimum_required(VERSION 3.16)
project("rlib-interation")


if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_compile_options(-Wall -Wextra -Werror)
  add_subdirectory(rlib)
  enable_testing()

  set(Boost_DEBUG 1)
  find_package(Boost REQUIRED)
  include_directories(${Boost_INCLUDE_DIRS})
  add_subdirectory(rlib-tests)
else()
  add_subdirectory(rlib)
endif()
