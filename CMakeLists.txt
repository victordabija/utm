cmake_minimum_required(VERSION 4.1)
project(utm C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ========================
# Libraries
# ========================
add_subdirectory(lib/queue)
add_subdirectory(lib/app_menu)
add_subdirectory(lib/application)
add_subdirectory(lib/linked_list)

# ========================
# Projects
# ========================
add_subdirectory(sda/lab-2)
add_subdirectory(sda/lab-6)
