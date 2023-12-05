cmake_minimum_required(VERSION 3.5)
project(TheGameOfLife)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(TheGameOfLife main.cpp)
target_link_libraries(TheGameOfLife PRIVATE sfml-system sfml-window sfml-graphics)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif ()

install(TARGETS ${CMAKE_PROJECT_NAME})