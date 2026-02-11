cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(kampad VERSION 1.0.0)

add_executable(kampad ../app/main.c
  ../src/keymapping.c
  ../src/input.c
  ../src/flags.c
  ../src/files.c
  ../src/buffer.c
)

find_library(CDL_LIB cdl PATHS ../lib/cdl/)

if (CDL_LIB)
  target_link_libraries(kampad PRIVATE ${CDL_LIB})
else()
  message("CDL NOT FOUND!")
endif()

find_library(NCURSES_LIB ncurses PATHS /usr/include/)

if (NCURSES_LIB)
  target_link_libraries(kampad PRIVATE ${NCURSES_LIB})
else () 
  message(FATAL_ERROR "curses not found")
endif()



