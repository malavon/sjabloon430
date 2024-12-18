cmake_minimum_required(VERSION 3.14)

project(pinout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pinout main.cpp)

find_package (SQLite3)
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (pinout ${SQLite3_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS pinout
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
