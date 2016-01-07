cmake_minimum_required(VERSION 2.8.9)
project(testdesignpatterns)

# Select c++ version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

#Bring the headers into the project
include_directories( ../inc inc/ ./../../../gtest/googletest/googletest/include ./../../../gtest/googletest/googlemock/include  )

#Add sources
file(GLOB SOURCES "src/*.cpp" "test/src/*.cpp")

#Link static lib
set ( PROJECT_LINK_LIBS gtest gmock designpatterns )
link_directories (./../../../gtest/googletest/googlemock/bin ./../../../gtest/googletest/googletest/bin ./../build/)

add_executable(testdesignpatterns ${SOURCES})
target_link_libraries( testdesignpatterns ${PROJECT_LINK_LIBS})