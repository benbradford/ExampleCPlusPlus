cmake_minimum_required(VERSION 2.8.9)
project(containers)

# Select c++ version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

#Bring the headers into the project
include_directories(inc/ )

#Add sources
file(GLOB SOURCES "src/*.cpp" )

#Link static lib
#set ( PROJECT_LINK_LIBS gtest gmock )
#link_directories (./../gtest/googletest/googlemock/bin ./../gtest/googletest/googletest/bin )

add_library(containers STATIC ${SOURCES})