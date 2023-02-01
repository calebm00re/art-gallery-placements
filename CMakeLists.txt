cmake_minimum_required(VERSION 3.20)
project(21f_pa01_caleb_s_team)

set(input01 "input/input.txt")

foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)

add_executable(21f_pa01_caleb_s_team src/main.cpp src/gallery.cpp src/gallery.h src/gallery_manager.cpp src/gallery_manager.h)