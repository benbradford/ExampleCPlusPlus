cmake_minimum_required(VERSION 2.8.9)
project(testexception)

# Select c++ version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

#Bring the headers into the project
include_directories( ../inc inc/ ./../../googletest/googletest/include ./../../googletest/googlemock/include  )

#Add sources
file(GLOB SOURCES "src/*.cpp" "test/src/*.cpp")

#Link static lib
set ( PROJECT_LINK_LIBS gtest gmock exception )
link_directories (./../../googletest/googlemock/bin ./../../googletest/googletest/bin ./../build/)

add_executable(testexception ${SOURCES})
target_link_libraries( testexception ${PROJECT_LINK_LIBS})