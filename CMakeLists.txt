cmake_minimum_required(VERSION 3.25)
project(TheCommunicator)

set(CMAKE_CXX_STANDARD 23)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0 REQUIRED)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(TheCommunicator main.cpp)
target_link_libraries(TheCommunicator ${GTKMM_LIBRARIES})