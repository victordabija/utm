add_library(sort STATIC
        sort.c
)

target_include_directories(sort
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
