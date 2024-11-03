set(USE_MSVC_RUNTIME_LIBRARY_DLL false CACHE BOOL "Use MSVC runtime library DLL")

set(POSITION_INDEPENDENT_CODE true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

cmake_minimum_required(VERSION 3.20)
project(Pentagram-Demo DESCRIPTION "A demo project for Pentagram" LANGUAGES CXX HOMEPAGE_URL "https://github.com/ShoweryCellar34/Pentagram-Demo")
file(GLOB app_source source/*.cpp)
add_executable(Ghoul-Engine ${app_source})
add_subdirectory(vendors/Pentagram)
target_include_directories(Ghoul-Engine PUBLIC headers)
target_link_libraries(Ghoul-Engine PUBLIC Pentagram)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS /MP")
endif()
if(GCC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic -fsanitize=address,undefined")
endif()

add_custom_target(delete_resources ALL COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_BINARY_DIR}/res/* COMMENT "Deleting old resources in binary directory")
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res COMMENT "Copying resources into binary directory")
