cmake_minimum_required(VERSION 3.8)
project(c-shooter)

set(VCPKG_ROOT "C:/vcpkg")

set(VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

set(C_STANDARD C23)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)

set(CSHOOTER_ARCH "x86")

elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)

set(CSHOOTER_ARCH "x64")

if(WIN32)
    set(CSHOOTER_PLATFORM "Win64")
elseif(LINUX)
    set(CSHOOTER_PLATFORM "Linux64")
endif()

endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CSHOOTER_OUT_DIR "${CMAKE_SOURCE_DIR}/CShooter/bin/${CMAKE_BUILD_TYPE}/${CSHOOTER_PLATFORM}")

set(EXECUTABLE_OUTPUT_PATH ${CSHOOTER_OUT_DIR})

add_subdirectory(thirdparty/cglm)

set(GLAD_SOURCES "ext/glad.c")

set(UFBX_SOURCES "ext/ufbx.c")

set(SOURCES 
"src/main.c"
"src/util/string_t.c"
"src/util/util.c"
"src/scene/scene.c"
"src/scene/ent/test_ent/test_ent.c"
 "src/input/input.c")

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCES} ${UFBX_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src )

target_link_libraries(${PROJECT_NAME} PRIVATE cglm )
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/cglm/include)

target_include_directories(${PROJECT_NAME} PRIVATE depend )

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)