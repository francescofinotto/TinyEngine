cmake_minimum_required(VERSION 3.0.0)
project(TinyEngineWindows VERSION 0.1.0)

file(GLOB PlatformFiles
src/*.cpp
src/*.c
)

add_library(${PROJECT_NAME} STATIC ${PlatformFiles})

target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE include/glad PRIVATE include/KHR)

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
