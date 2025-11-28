cmake_minimum_required(VERSION 3.0)

project(Advent-of-Code-2024
        VERSION 0.1
        DESCRIPTION "Calendar of small programming puzzles"
        HOMEPAGE_URL "https://github.com/Cornichon0097/Advent-of-Code/2024"
        LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE c_std_90)

set(gcc_like_c "$<COMPILE_LANG_AND_ID:C,GNU>")
target_compile_options(compiler_flags INTERFACE
    $<${gcc_like_c}:$<BUILD_INTERFACE:-Wall;-Wextra;-g>>
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(libaoc)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
