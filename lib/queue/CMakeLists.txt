add_library(queue STATIC
        queue_d.c
)

target_include_directories(queue
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
