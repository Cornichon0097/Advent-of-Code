add_library(aoc
    input.c)

target_link_libraries(aoc
    INTERFACE
    compiler_flags)

target_include_directories(aoc
    PUBLIC
    "${PROJECT_SOURCE_DIR}/libaoc/include")
