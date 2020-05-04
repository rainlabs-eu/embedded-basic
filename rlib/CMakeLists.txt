project(rlib)


file(GLOB_RECURSE SRC "src/*.cpp")
add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/rlib)
