cmake_minimum_required(VERSION 3.20.2)

project(sandbox)

set(SOURCES src/main.c)
set(LIBRARY_DIR "${CMAKE_CURRENT_LIST_DIR}/lib")
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARY_DIR}/SDL2main.lib ${LIBRARY_DIR}/SDL2.lib)
