cmake_minimum_required(VERSION 3.14)

project(pinout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (SQLite3)
find_package (Curses)

set(CCCURSES_HEADERS
    cccurses/cccurses.hpp
    cccurses/color-internal.hpp
    cccurses/colors.hpp
    cccurses/error.hpp
    cccurses/form.hpp
    cccurses/input.hpp
    cccurses/support.hpp
    cccurses/window.hpp
)

set(PINOUT_HEADERS
    database.hpp
    database-files.hpp
    ui.hpp
)

add_executable(pinout
    database.cpp
    database-files.cpp
    pinout.cpp
    ui.cpp

    # these are here only for QTCreator
    ${CCCURSES_HEADERS}
    ${PINOUT_HEADERS}
)

target_include_directories  (pinout PRIVATE ${SQLite3_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS})
target_link_libraries	    (pinout PRIVATE ${SQLite3_LIBRARIES} ${CURSES_LIBRARIES})

target_compile_definitions  (pinout PUBLIC DB_DIRECTORY="${CMAKE_SOURCE_DIR}/../db/sql")
# todo: option? and check for gcc/clang
target_compile_options	    (pinout PUBLIC -Werror)
target_compile_options	    (pinout PUBLIC -Wall -Wextra -Wpedantic)

include(GNUInstallDirs)
install(TARGETS pinout
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
