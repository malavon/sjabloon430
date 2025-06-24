cmake_minimum_required(VERSION 3.14)

project(pinout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (SQLite3)
find_package (Curses)

set(DB_PROJECT_DIR ${CMAKE_SOURCE_DIR}/../db)

set(CCCURSES_HEADERS
    cccurses/cccurses.hpp
    cccurses/color-internal.hpp
    cccurses/colors.hpp
    cccurses/error.hpp
    cccurses/form.hpp
    cccurses/input.hpp
    cccurses/support.hpp
    cccurses/window.hpp
    cccurses/layout/layout.hpp
    cccurses/layout/absolute-layout.hpp
    cccurses/layout/flow-layout.hpp
    cccurses/layout/column-layout.hpp
)

set(PINOUT_HEADERS
    ${DB_PROJECT_DIR}/database-files.hpp
    database.hpp
    ui.hpp
    util.hpp
)

add_executable(pinout
    ${DB_PROJECT_DIR}/database-files.cpp
    database.cpp
    pinout.cpp
    ui.cpp

    # these are here only for QTCreator
    ${CCCURSES_HEADERS}
    ${PINOUT_HEADERS}
)

target_include_directories  (pinout PRIVATE ${SQLite3_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS} ${DB_PROJECT_DIR})
target_link_libraries	    (pinout PRIVATE ${SQLite3_LIBRARIES} ${CURSES_LIBRARIES})

target_compile_definitions  (pinout PUBLIC DB_DIRECTORY="${DB_PROJECT_DIR}/sql")

include(GNUInstallDirs)
install(TARGETS pinout
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
