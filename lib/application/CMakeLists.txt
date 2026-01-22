add_library(application STATIC
        application.c
)

target_include_directories(application
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
