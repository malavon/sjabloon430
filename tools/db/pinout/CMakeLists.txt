cmake_minimum_required(VERSION 3.14)

project(pinout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pinout		main.cpp)
add_executable(pinout-ftx	main-ftx.cpp)
add_executable(pinout-ncurses	main-ncurses.cpp)

find_package (SQLite3)
find_package(Curses)
find_package(ftxui)

set(CURSES_NEED_NCURSES, YES)

target_include_directories(pinout	    PRIVATE ${SQLite3_INCLUDE_DIRS})
target_include_directories(pinout-ftx	    PRIVATE ${SQLite3_INCLUDE_DIRS} ${ftxui_INCLUDE_DIRS})
target_include_directories(pinout-ncurses   PRIVATE ${SQLite3_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS})

target_link_libraries (pinout ${SQLite3_LIBRARIES})

target_link_libraries(pinout-ftx
  PRIVATE ftxui::screen
  ftxui::dom
  ftxui::component  # Not needed for this example.
  ${SQLite3_LIBRARIES}
)

target_link_libraries (pinout-ncurses ${SQLite3_LIBRARIES} ${CURSES_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS pinout
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
