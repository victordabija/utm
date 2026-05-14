add_executable(lab5 main.c handlers.c)

target_link_libraries(lab5
        PRIVATE
        app_menu
        application
        stack
        libcar
        txt_file
        sort
        linked_list
)
