cmake_minimum_required(VERSION 3.25)
project(TheGameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(TheGameOfLife main.cpp)
target_link_libraries(TheGameOfLife sfml-system sfml-window sfml-graphics -static)
