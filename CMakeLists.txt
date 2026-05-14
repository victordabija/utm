cmake_minimum_required(VERSION 4.1)
project(utm C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ========================
# Libraries
# ========================
add_subdirectory(lib/libcar)
add_subdirectory(lib/app_menu)
add_subdirectory(lib/application)
add_subdirectory(lib/linked_list)
add_subdirectory(lib/bin_file)
add_subdirectory(lib/txt_file)
add_subdirectory(lib/sort)
add_subdirectory(lib/stack)
add_subdirectory(lib/array)

# ========================
# Projects
# ========================
add_subdirectory(sda/lab-1)
add_subdirectory(sda/lab-2)
add_subdirectory(sda/lab-3)
add_subdirectory(sda/lab-4)
add_subdirectory(sda/lab-5)
add_subdirectory(sda/lab-6)
