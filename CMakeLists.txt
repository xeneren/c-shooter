cmake_minimum_required(VERSION 3.20)
project(c-shooter)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(thirdparty/cglm)

file(GLOB_RECURSE SOURCES "src/*.c" "ext/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src )

target_link_libraries(${PROJECT_NAME} PRIVATE cglm )
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/cglm/include )

target_include_directories(${PROJECT_NAME} PRIVATE depend )

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)