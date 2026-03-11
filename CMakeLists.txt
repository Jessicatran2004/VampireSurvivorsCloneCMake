cmake_minimum_required(VERSION 3.21)

project(VampireSurvivorsClone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(VampireSurvivorsClone ${SOURCES} "include/Projectile.h" "src/Projectile.cpp" "include/Weapon.h" "include/DirectionWeapon.h" "include/MouseWeapon.h" "src/DirectionWeapon.cpp" "src/MouseWeapon.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/W4 /Zi>
        $<$<CONFIG:Release>:/O2>
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-Wall -g>
        $<$<CONFIG:Release>:-O2>
    )
endif()