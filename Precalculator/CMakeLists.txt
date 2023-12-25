#Creates the data file of precalculated prime decompositions

cmake_minimum_required(VERSION 3.10)

project(Precalculator)

add_executable(precalculator ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(precalculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
