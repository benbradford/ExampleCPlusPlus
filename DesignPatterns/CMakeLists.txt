cmake_minimum_required(VERSION 2.8.9)
project(designpatterns)

# Select c++ version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

#Bring the headers into the project
include_directories(inc/ )

#Add sources
file(GLOB SOURCES "src/DesignPatterns/AbstractFactory/*.cpp" "src/DesignPatterns/Command/*.cpp" "src/DesignPatterns/EntityComponent/*.cpp" "src/DesignPatterns/Observer/*.cpp" "src/DesignPatterns/Observer/FlexibleSubject/*.cpp" "src/DesignPatterns/Singleton/AdvancedManagedSingleton/*.cpp" "src/DesignPatterns/Singleton/BasicSoundSingleton/*.cpp" "src/DesignPatterns/Singleton/SingletonAsServices/*.cpp" "src/DesignPatterns/State/BasicState/*.cpp" "src/DesignPatterns/State/StateStack/*.cpp")

add_library(designpatterns STATIC ${SOURCES})