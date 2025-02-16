cmake_minimum_required(VERSION 3.14)

project(pinout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (SQLite3)
find_package (Curses)

add_executable(pinout
    database.cpp
    pinout.cpp

    # these are here only for QTCreator
    cccurses/cccurses.hpp
    cccurses/colors.hpp
    cccurses/error.hpp
    cccurses/form.hpp
    cccurses/window.hpp
    cccurses/layout/layout.hpp
    cccurses/layout/absolute-layout.hpp
    cccurses/layout/flow-layout.hpp
    cccurses/layout/column-layout.hpp
)

target_include_directories  (pinout PRIVATE ${SQLite3_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS})
target_link_libraries	    (pinout PRIVATE ${SQLite3_LIBRARIES} ${CURSES_LIBRARIES})

target_compile_definitions  (pinout PUBLIC DB_DIRECTORY="${CMAKE_SOURCE_DIR}/../db")

include(GNUInstallDirs)
install(TARGETS pinout
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
