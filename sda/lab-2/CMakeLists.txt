add_executable(lab2 main.c handlers.c)

target_link_libraries(lab2
        PRIVATE
        app_menu
        application
        libcar
        sort
)
