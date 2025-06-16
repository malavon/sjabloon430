cmake_minimum_required(VERSION 3.14)

project(device LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEVICE_HEADERS
    database.hpp
    # shared import/export database-files.hpp
)

add_executable(device
    device.cpp

    ${DEVICE_HEADERS}
    database.cpp
    )

find_package (SQLite3)
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (device ${SQLite3_LIBRARIES})

# cmake option? gcc/clang check too
target_compile_options	    (device PUBLIC -Werror)
target_compile_options	    (device PUBLIC -Wall -Wextra -Wpedantic)

include(GNUInstallDirs)
install(TARGETS device
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
