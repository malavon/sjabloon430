cmake_minimum_required(VERSION 3.14)

project(devices LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(devices main.cpp)

find_package (SQLite3)
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (devices ${SQLite3_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS devices
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
