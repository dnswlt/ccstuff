cmake_minimum_required(VERSION 3.10.0)
project(race)

find_package(Threads)

# include_directories(include)

file(GLOB SOURCES *.cc)

add_executable(race ${SOURCES})
target_link_libraries (race ${CMAKE_THREAD_LIBS_INIT})

