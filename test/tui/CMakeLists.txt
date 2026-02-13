cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tui VERSION 1.0.0)

add_executable(tui tui.c
  ../../src/keymapping.c
  ../../src/terminal.c
  ../../src/rows.c
)

find_library(CDL_LIB cdl PATHS ../../lib/cdl/)

if (CDL_LIB)
  target_link_libraries(tui PRIVATE ${CDL_LIB})
else()
  message("CDL NOT FOUND!")
endif()

