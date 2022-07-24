cmake_minimum_required(VERSION 3.0.0)
project(TinyEngineWindows VERSION 0.1.0)

file(GLOB PlatformFiles
src/*.cpp
src/*.c
)

add_library(${PROJECT_NAME} STATIC ${PlatformFiles})
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE include/debug/glad PRIVATE include/debug/KHR)
file(GLOB DebugFiles
src/debug/*.cpp
src/debug/*.c
)
target_sources(${PROJECT_NAME} ${DebugFiles})
else()
target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE include/glad PRIVATE include/KHR)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
