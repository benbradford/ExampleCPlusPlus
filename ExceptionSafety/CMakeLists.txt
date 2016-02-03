cmake_minimum_required(VERSION 2.8.9)
project(exception)

# Select c++ version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

#Bring the headers into the project
include_directories(inc/ )

#Add sources
file(GLOB SOURCES "src/*.cpp")

add_library(exception STATIC ${SOURCES})