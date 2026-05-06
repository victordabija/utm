add_executable(lab4 main.c handlers.c)

target_link_libraries(lab4
        PRIVATE
        app_menu
        application
        txt_file
        libcar
        sort
)
