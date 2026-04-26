add_library(bin_file STATIC
        bin_file.c
)

target_include_directories(bin_file
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
