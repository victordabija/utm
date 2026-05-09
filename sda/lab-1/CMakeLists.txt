add_executable(lab1 main.c handlers/handlers_1d.c handlers/handlers_2d.c helpers/helpers.c)

target_link_libraries(lab1
        PRIVATE
        app_menu
        application
        libcar
        array
        sort
)
