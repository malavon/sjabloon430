cmake_minimum_required(VERSION 3.14)

project(device LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DB_PROJECT_DIR ${CMAKE_SOURCE_DIR}/../db)

set(DEVICE_HEADERS
    ${DB_PROJECT_DIR}/database-files.hpp
    database.hpp
)

add_executable(device
    ${DB_PROJECT_DIR}/database-files.cpp
    database.cpp
    device.cpp

    ${DEVICE_HEADERS}
)

find_package (SQLite3)
target_include_directories  (device PRIVATE ${SQLite3_INCLUDE_DIRS} ${DB_PROJECT_DIR})
target_link_libraries       (device ${SQLite3_LIBRARIES})

target_compile_definitions  (device PUBLIC DB_DIRECTORY="${DB_PROJECT_DIR}/sql")

# cmake option? gcc/clang check too
target_compile_options	    (device PUBLIC -Werror)
target_compile_options	    (device PUBLIC -Wall -Wextra -Wpedantic)

include(GNUInstallDirs)
install(TARGETS device
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
