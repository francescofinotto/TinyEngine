cmake_minimum_required(VERSION 3.0.0)

project(TinyEngine VERSION 0.0.1)

add_subdirectory(TinyEngine)
add_subdirectory(Engine)

add_definitions(-DWIN32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
