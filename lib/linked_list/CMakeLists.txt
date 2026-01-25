add_library(linked_list STATIC
        linked_list.c
)

target_include_directories(linked_list
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
