add_executable(lab6 main.c handlers.c)

target_link_libraries(lab6
        PRIVATE
        linked_list
        app_menu
        application
        sort
        libcar
)
