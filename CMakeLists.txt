cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("raylib")

project(snake)

file(GLOB SRC "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(snake PUBLIC raylib)