add_library(app_menu STATIC
        app_menu.c
)

target_include_directories(app_menu
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app_menu
        PRIVATE
        application
        m
)

