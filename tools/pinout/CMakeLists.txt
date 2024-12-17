cmake_minimum_required(VERSION 3.14)

project(pinout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pinout		main.cpp)

find_package (SQLite3)

target_include_directories(pinout	    PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries (pinout ${SQLite3_LIBRARIES})

# todo: option? and check for gcc/clang
target_compile_options	    (pinout PUBLIC -Werror)
target_compile_options	    (pinout PUBLIC -Wall -Wextra -Wpedantic)

include(GNUInstallDirs)
install(TARGETS pinout
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
