add_executable(lab3 main.c handlers.c)

target_link_libraries(lab3
        PRIVATE
        app_menu
        application
        bin_file
        libcar
        sort
)
