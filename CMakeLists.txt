cmake_minimum_required(VERSION 3.21)
project(VampireSurvivorsCloneCMake)

find_package(raylib CONFIG REQUIRED)

add_executable(VampireSurvivorsCloneCMake main.cpp)

target_link_libraries(VampireSurvivorsCloneCMake PRIVATE raylib)