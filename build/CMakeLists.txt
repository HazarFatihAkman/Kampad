cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(kampad VERSION 1.0.0)
add_executable(kampad ../app/main.c
  ../src/terminal.c
  ../src/keymapping.c
  ../src/new_file.c
)

