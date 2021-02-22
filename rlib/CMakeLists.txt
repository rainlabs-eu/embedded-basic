project(rlib)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp")
add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/rlib)
target_include_directories(${PROJECT_NAME} PRIVATE include/rlib/detail)

add_library(${PROJECT_NAME}-shared SHARED ${SRC})
target_include_directories(${PROJECT_NAME}-shared PUBLIC include/)
target_include_directories(${PROJECT_NAME}-shared PRIVATE include/rlib)
target_include_directories(${PROJECT_NAME}-shared PRIVATE include/rlib/detail)

add_library(${PROJECT_NAME}-static STATIC ${SRC})
target_include_directories(${PROJECT_NAME}-static PUBLIC include/)
target_include_directories(${PROJECT_NAME}-static PRIVATE include/rlib)
target_include_directories(${PROJECT_NAME}-static PRIVATE include/rlib/detail)
