add_library(array STATIC
        array.c
)

target_include_directories(array
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(array
        PRIVATE
        application
)