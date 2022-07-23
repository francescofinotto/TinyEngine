cmake_minimum_required(VERSION 3.0.0)
project(TinyEngineEngine VERSION 0.1.0)

file(GLOB PlatformFiles
src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${PlatformFiles})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib PUBLIC TinyEngineWindows PUBLIC TinyEnginePlatform)



add_subdirectory(_Platform)
add_subdirectory(_Windows)



