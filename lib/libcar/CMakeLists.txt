add_library(libcar STATIC
        libcar.c
)

target_include_directories(libcar
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(libcar
        PRIVATE
        application
        sort
)
