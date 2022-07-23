cmake_minimum_required(VERSION 3.0.0)
project(TinyEngineEngine VERSION 0.1.0)

file(GLOB PlatformFiles
src/*.cpp
src/*.c
)
add_library(${PROJECT_NAME} STATIC ${PlatformFiles})

target_include_directories(${PROJECT_NAME} INTERFACE include include/glad include/KHR)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)