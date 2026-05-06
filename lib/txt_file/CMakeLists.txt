add_library(txt_file STATIC
        txt_file.c
)

target_include_directories(txt_file
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(txt_file
        PRIVATE
        sort
)